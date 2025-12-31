import subprocess
from multiprocessing import Pool, cpu_count
from pathlib import Path

CPP_FILE = "cp.cpp"
SOL_BIN = "./cp.out"
SCORER_BIN = "./scorer.out"
INPUT_DIR = Path("tools/in")
OUT_DIR = Path("output")

OUT_DIR.mkdir(exist_ok=True)

def compile_all():
    print("Compiling solution...")
    subprocess.run(
        ["g++", "-O2", "-std=gnu++20", "cp.cpp", "-o", "cp.out"],
        check=True
    )

    print("Compiling scorer...")
    subprocess.run(
        ["g++", "-O2", "-std=gnu++20", "scorer.cpp", "-o", "scorer.out"],
        check=True
    )

def run_one(input_file):
    out_file = OUT_DIR / (input_file.stem + ".out")

    # run solution
    with open(input_file) as fin, open(out_file, "w") as fout:
        subprocess.run([SOL_BIN], stdin=fin, stdout=fout, check=True)

    # run scorer
    res = subprocess.run(
        [SCORER_BIN, str(input_file), str(out_file)],
        capture_output=True,
        text=True,
        check=True
    )

    score = float(res.stdout.strip())
    return input_file.name, score

def main():
    compile_all()

    inputs = sorted(INPUT_DIR.glob("000*.txt"))
    print(f"Running {len(inputs)} tests")

    workers = min(cpu_count(), len(inputs))
    with Pool(workers) as p:
        results = p.map(run_one, inputs)

    total = 0
    for name, score in results:
        print(f"{name}: {score}")
        total += score

    print("=" * 40)
    print("TOTAL SCORE:", total)

if __name__ == "__main__":
    main()
