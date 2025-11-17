import sys
import math
import random

def usage():
    print("Usage: python3 graph-subset.py <fraction> [input_file] [output_file] [seed]")
    print("  <fraction> : portion of edges to keep, e.g., 0.25 for 25% or 25 for 25%")
    print("  [input_file]  (optional): default = graph.txt")
    print("  [output_file] (optional): default = graph-<fraction*100>.txt")
    print("  [seed]       (optional): random seed for reproducibility (e.g., 42)")
    sys.exit(1)

def main():
    if len(sys.argv) < 2 or sys.argv[1] in ("-h", "--help"):
        usage()

    # parse fraction
    try:
        frac = float(sys.argv[1])
    except ValueError:
        usage()

    # allow both 0.25 and 25 as 25%
    if frac > 1.0:
        frac = frac / 100.0

    if not (0.0 < frac <= 1.0):
        print("Error: fraction must be in (0, 1].")
        sys.exit(1)

    input_file = "graph.txt"
    if len(sys.argv) >= 3:
        input_file = sys.argv[2]

    # default output file name: graph-25.txt, graph-50.txt, etc.
    if len(sys.argv) >= 4:
        output_file = sys.argv[3]
    else:
        pct = int(round(frac * 100))
        output_file = f"graph-{pct}.txt"

    # optional seed
    seed = 42
    if len(sys.argv) >= 5:
        try:
            seed = int(sys.argv[4])
        except ValueError:
            print("Warning: invalid seed, using default seed 42.")

    random.seed(seed)

    with open(input_file, "r") as f:
        lines = f.readlines()

    n = len(lines)
    k = max(1, int(math.floor(n * frac)))

    # randomly pick k edges without replacement
    subset = random.sample(lines, k)

    with open(output_file, "w") as f:
        f.writelines(subset)

    print(f"Total edges: {n}, randomly kept: {k} ({frac*100:.1f}%), written to {output_file} (seed={seed})")

if __name__ == "__main__":
    main()
