import re
import sys

if len(sys.argv) != 5:
    print("Usage: python3 extract_kernel_by_pc.py <full_log> <out_log> <start_pc_hex> <end_pc_hex>")
    sys.exit(1)

full_log = sys.argv[1]
out_log = sys.argv[2]
start_pc = int(sys.argv[3], 16)
end_pc = int(sys.argv[4], 16)

pc_re = re.compile(r"core\s+\d+:\s+(0x[0-9a-fA-F]+)\s+\(")

count = 0
with open(full_log, errors="ignore") as fin, open(out_log, "w") as fout:
    for line in fin:
        m = pc_re.search(line)
        if not m:
            continue
        pc = int(m.group(1), 16)
        if start_pc <= pc <= end_pc:
            fout.write(line)
            count += 1

print(f"Wrote: {out_log}")
print(f"Kernel lines: {count}")
