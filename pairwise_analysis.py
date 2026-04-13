import re
import sys
from collections import Counter

if len(sys.argv) != 2:
    print("Usage: python3 pairwise_analysis.py <kernel_log>")
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

last_writer = {}
insns = []
opcnt = Counter()
paircnt = Counter()
raw_total = 0

with open(LOG, errors="ignore") as f:
    for idx, line in enumerate(f):
        m = insn_re.search(line)
        if not m:
            continue
        pc = m.group(1)
        dis = m.group(2)
        rd, reads, op, cls = guess_rd_reads(dis)
        insns.append((idx, pc, dis, rd, reads, op, cls))
        opcnt[op] += 1

load_mul = []
mul_add = []
all_raw = []

for idx, pc, dis, rd, reads, op, cls in insns:
    for r in reads:
        if r in last_writer:
            prev_idx, prev_cls = last_writer[r]
            dist = idx - prev_idx
            raw_total += 1
            all_raw.append(dist)
            paircnt[(prev_cls, cls)] += 1
            if prev_cls == "load" and cls == "mul":
                load_mul.append(dist)
            if prev_cls == "mul" and cls == "add":
                mul_add.append(dist)
    if rd:
        last_writer[rd] = (idx, cls)

print("Kernel dynamic instructions:", len(insns))
print("RAW total:", raw_total)
print("RAW/insn:", raw_total / len(insns) if insns else 0.0)
print("load->mul:", len(load_mul), summarize(load_mul))
print("mul->add:", len(mul_add), summarize(mul_add))
print("all RAW:", summarize(all_raw))
print("Top ops:", opcnt.most_common(12))
print("Top pair types:", paircnt.most_common(12))
