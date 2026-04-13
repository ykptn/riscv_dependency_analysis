import re
import sys
from collections import Counter

if len(sys.argv) != 2:
    print("Usage: python3 mul_centric_analysis.py <kernel_log>")
    sys.exit(1)

LOG = sys.argv[1]

insn_re = re.compile(r"core\s+\d+:\s+(0x[0-9a-fA-F]+)\s+\(0x[0-9a-fA-F]+\)\s+(.*)$")

abi_to_x = {
  "zero":"x0","ra":"x1","sp":"x2","gp":"x3","tp":"x4",
  "t0":"x5","t1":"x6","t2":"x7",
  "s0":"x8","fp":"x8","s1":"x9",
  "a0":"x10","a1":"x11","a2":"x12","a3":"x13","a4":"x14","a5":"x15","a6":"x16","a7":"x17",
  "s2":"x18","s3":"x19","s4":"x20","s5":"x21","s6":"x22","s7":"x23","s8":"x24","s9":"x25","s10":"x26","s11":"x27",
  "t3":"x28","t4":"x29","t5":"x30","t6":"x31",
}
reg_tok = re.compile(r"\b(x(?:[12]?\d|3[01])|zero|ra|sp|gp|tp|t[0-6]|s(?:1[01]|[0-9])|fp|a[0-7])\b")

def norm(r):
    return r if r.startswith("x") else abi_to_x.get(r, r)

def split_tokens(disasm):
    return disasm.replace(",", " ").replace("(", " ").replace(")", " ").split()

def classify_op(op):
    if op in ("lw","lh","lb","lbu","lhu","ld","lwu","flw","fld","c.lw","c.ld","c.lwsp","c.ldsp"):
        return "load"
    if op in ("sw","sh","sb","sd","fsw","fsd","c.sw","c.sd","c.swsp","c.sdsp"):
        return "store"
    if op in ("mul","mulh","mulhu","mulhsu","mulw"):
        return "mul"
    if op in ("add","addw","addi","addiw","c.add","c.addw","c.addi","c.addiw","sub","subw","c.sub","c.subw"):
        return "add"
    if op.startswith("b") or op in ("beq","bne","blt","bge","bltu","bgeu","c.beqz","c.bnez","jal","jalr","c.j","c.jal"):
        return "branch"
    return "other"

def guess_rd_reads(disasm):
    toks = split_tokens(disasm)
    if not toks:
        return None, [], "?", "other"
    op = toks[0]
    regs = [norm(r) for r in reg_tok.findall(disasm)]
    cls = classify_op(op)

    if cls in ("store","branch"):
        return None, regs, op, cls

    if op in ("jal","c.jal"):
        rd = regs[0] if regs else None
        return rd, [], op, "branch"
    if op == "jalr":
        rd = regs[0] if len(regs) >= 1 else None
        reads = regs[1:2] if len(regs) >= 2 else []
        return rd, reads, op, "branch"

    rd = regs[0] if regs else None
    reads = regs[1:] if len(regs) > 1 else []
    return rd, reads, op, cls

def summarize(vals):
    if not vals:
        return {"n": 0}
    vals = sorted(vals)
    n = len(vals)
    def pct(p):
        idx = min(n - 1, int(p * n))
        return vals[idx]
    return {
        "n": n,
	"min": vals[0],
        "avg": sum(vals) / n,
        "p50": pct(0.50),
        "p90": pct(0.90),
        "max": vals[-1],
    }

insns = []
with open(LOG, errors="ignore") as f:
    for idx, line in enumerate(f):
        m = insn_re.search(line)
        if not m:
            continue
        pc = m.group(1)
        dis = m.group(2)
        rd, reads, op, cls = guess_rd_reads(dis)
        insns.append({
            "idx": idx,
            "pc": pc,
            "dis": dis,
            "rd": rd,
            "reads": reads,
            "op": op,
            "cls": cls
        })

print(f"Kernel trace loaded: {LOG}")
print("Dynamic instructions:", len(insns))

last_writer = {}
producer_distances = []
producer_types = Counter()

for ins in insns:
    if ins["cls"] == "mul":
        local_best = None
        local_type = None
        for r in ins["reads"]:
            if r in last_writer:
                prev_idx, prev_cls = last_writer[r]
                dist = ins["idx"] - prev_idx
                if local_best is None or dist < local_best:
                    local_best = dist
                    local_type = prev_cls
        if local_best is not None:
            producer_distances.append(local_best)
            producer_types[local_type] += 1

    if ins["rd"]:
        last_writer[ins["rd"]] = (ins["idx"], ins["cls"])

nearest_consumer_distances = []
nearest_consumer_types = Counter()

for i, ins in enumerate(insns):
    if ins["cls"] != "mul" or not ins["rd"]:
        continue
    dest = ins["rd"]

    for j in range(i + 1, len(insns)):
        nxt = insns[j]
        if dest in nxt["reads"]:
            nearest_consumer_distances.append(j - i)
            nearest_consumer_types[nxt["cls"]] += 1
            break
        if nxt["rd"] == dest:
            break

print("\n=== MUL-CENTRIC RESULTS ===")
print("Total mul instructions:", sum(1 for x in insns if x["cls"] == "mul"))
print("\nNearest producer -> mul distance stats:")
print(summarize(producer_distances))
print("Nearest producer types:", producer_types.most_common())
print("\nMul -> nearest consumer distance stats:")
print(summarize(nearest_consumer_distances))
print("Nearest consumer types:", nearest_consumer_types.most_common())

chain_lengths = []
final_consumer_types = Counter()

for i, ins in enumerate(insns):
    if ins["cls"] != "mul" or not ins["rd"]:
        continue

    current_reg = ins["rd"]
    current_idx = i
    chain_len = 0
    final_type = None

    while True:
        next_user = None
        for j in range(current_idx + 1, len(insns)):
            nxt = insns[j]
            if current_reg in nxt["reads"]:
                next_user = nxt
                break
            if nxt["rd"] == current_reg:
                break

        if next_user is None:
            break

        chain_len += 1
        final_type = next_user["cls"]

        if next_user["rd"] and next_user["cls"] not in ("store", "branch"):
            current_reg = next_user["rd"]
            current_idx = next_user["idx"]
        else:
            break

    if chain_len > 0:
        chain_lengths.append(chain_len)
        final_consumer_types[final_type] += 1

print("\n=== MUL FULL CHAIN RESULTS ===")
print("Total mul analyzed:", len(chain_lengths))
print("Chain length stats:", summarize(chain_lengths))
print("Final consumer types:", final_consumer_types.most_common())
