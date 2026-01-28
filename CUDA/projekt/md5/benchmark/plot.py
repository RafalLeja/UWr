#!/usr/bin/env python3
import argparse
import hashlib
import os
import re
import secrets
import subprocess
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Tuple

import matplotlib.pyplot as plt


@dataclass
class BenchResult:
    time_sec: float
    speed_mhash: float


CHARSET_MAP = {
    "n": "0123456789",
    "l": "abcdefghijklmnopqrstuvwxyz",
    "u": "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "s": "!\"#$%&'()*+,-./;:<=>?@[\\]^_`{|}~",
}


def build_charset(flags: str) -> str:
    charset = "".join(CHARSET_MAP[c] for c in flags if c in CHARSET_MAP)
    if not charset:
        charset = "".join(CHARSET_MAP.values())
    return charset


def random_password(length: int, charset: str) -> str:
    return "".join(secrets.choice(charset) for _ in range(length))


def write_md5_hash(password: str, out_file: Path) -> None:
    digest = hashlib.md5(password.encode("utf-8")).hexdigest()
    out_file.write_text(digest + "\n", encoding="utf-8")


def parse_app_output(output: str) -> Dict[int, BenchResult]:
    results: Dict[int, BenchResult] = {}
    pattern = re.compile(r"^\s*(\d+)\s*;\s*([0-9.eE+-]+)\s*;\s*([0-9.eE+-]+)\s*$")
    for line in output.splitlines():
        match = pattern.match(line)
        if not match:
            continue
        length = int(match.group(1))
        time_sec = float(match.group(2))
        speed_mhash = float(match.group(3))
        results[length] = BenchResult(time_sec=time_sec, speed_mhash=speed_mhash)
    return results


def run_app(
    app_path: Path,
    password_file: Path,
    max_len: int,
    charset_flags: str,
    device: str,
    timeout_sec: float | None = None,
) -> tuple[Dict[int, BenchResult], str]:
    cmd = [
        str(app_path),
        "-b",
        "-p",
        "-i",
        str(password_file),
        "-m",
        str(max_len),
        "-o",
        "/dev/null",
    ]

    if device:
        cmd.extend(["-d", device])

    for flag in charset_flags:
        if flag in CHARSET_MAP:
            cmd.append(f"-{flag}")

    completed = subprocess.run(
        cmd,
        check=True,
        text=True,
        capture_output=True,
        timeout=timeout_sec,
    )
    combined = "\n".join([completed.stdout, completed.stderr]).strip()
    return parse_app_output(combined), combined


def average_results(all_runs: List[Dict[int, BenchResult]]) -> Dict[int, BenchResult]:
    sums: Dict[int, Tuple[float, float, int]] = {}
    for run in all_runs:
        for length, result in run.items():
            time_sum, speed_sum, count = sums.get(length, (0.0, 0.0, 0))
            sums[length] = (
                time_sum + result.time_sec,
                speed_sum + result.speed_mhash,
                count + 1,
            )

    averaged: Dict[int, BenchResult] = {}
    for length, (time_sum, speed_sum, count) in sums.items():
        averaged[length] = BenchResult(
            time_sec=time_sum / count,
            speed_mhash=speed_sum / count,
        )
    return averaged


def plot_results(
    results_map: Dict[str, Dict[int, BenchResult]],
    out_path: Path,
    title: str,
) -> None:
    fig, (ax_time, ax_speed) = plt.subplots(2, 1, figsize=(8, 8), sharex=True)
    fig.suptitle(title)

    for label, results in results_map.items():
        lengths = sorted(results.keys())
        times = [results[l].time_sec for l in lengths]
        speeds = [results[l].speed_mhash for l in lengths]
        ax_time.plot(lengths, times, marker="o", label=label)
        ax_speed.plot(lengths, speeds, marker="o", label=label)

    ax_time.set_ylabel("Time (s)")
    ax_time.grid(True, alpha=0.3)
    ax_time.legend()

    ax_speed.set_ylabel("Speed (million hashes/s)")
    ax_speed.set_yscale("log")
    ax_speed.set_xlabel("Password length")
    ax_speed.grid(True, alpha=0.3)
    ax_speed.legend()

    fig.tight_layout()
    fig.savefig(out_path, dpi=160)


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Benchmark MD5 cracking and plot averages."
    )
    parser.add_argument("--app", default="../bin/app", help="Path to app binary")
    parser.add_argument(
        "--password-file", default="../password", help="Path to password file"
    )
    parser.add_argument(
        "--max-len", type=int, default=7, help="Max password length (fallback)"
    )
    parser.add_argument(
        "--max-len-cpu", type=int, default=None, help="Max password length for CPU"
    )
    parser.add_argument(
        "--max-len-gpu", type=int, default=None, help="Max password length for GPU"
    )
    parser.add_argument(
        "--pw-len", type=int, default=None, help="Generated password length"
    )
    parser.add_argument(
        "--iterations", type=int, default=5, help="Number of runs to average"
    )
    parser.add_argument("--charset", default="nlu", help="Charset flags: n,l,u,s")
    parser.add_argument("--device", default="cpu", help="Device: cpu or cuda")
    parser.add_argument("--device2", default="cuda", help="Second device: cpu or cuda")
    parser.add_argument(
        "--cpu-timeout",
        type=float,
        default=120.0,
        help="Timeout in seconds for CPU runs",
    )
    parser.add_argument("--out", default="benchmark.png", help="Output plot path")

    args = parser.parse_args()

    app_path = Path(args.app).expanduser().resolve()
    password_file = Path(args.password_file).expanduser().resolve()
    out_path = Path(args.out).expanduser().resolve()

    if not app_path.exists():
        raise SystemExit(f"App not found: {app_path}")

    charset = build_charset(args.charset)

    def device_max_len(device: str) -> int:
        if device == "cpu" and args.max_len_cpu is not None:
            return args.max_len_cpu
        if device == "cuda" and args.max_len_gpu is not None:
            return args.max_len_gpu
        return args.max_len

    if args.pw_len is not None:
        pw_len = args.pw_len
    else:
        max_candidates = [args.max_len]
        if args.max_len_cpu is not None:
            max_candidates.append(args.max_len_cpu)
        if args.max_len_gpu is not None:
            max_candidates.append(args.max_len_gpu)
        pw_len = max(max_candidates)

    def run_device(device_label: str, device: str) -> Dict[int, BenchResult] | None:
        all_runs: List[Dict[int, BenchResult]] = []
        for idx in range(args.iterations):
            print(
                f"{device_label} run {idx + 1}/{args.iterations}: generating password...",
                flush=True,
            )
            password = random_password(pw_len, charset)
            write_md5_hash(password, password_file)
            print(
                f"{device_label} run {idx + 1}/{args.iterations}: running app...",
                flush=True,
            )
            timeout = args.cpu_timeout if device == "cpu" else None
            max_len = device_max_len(device)
            try:
                run_results, raw_output = run_app(
                    app_path=app_path,
                    password_file=password_file,
                    max_len=max_len,
                    charset_flags=args.charset,
                    device=device,
                    timeout_sec=timeout,
                )
            except subprocess.TimeoutExpired:
                print(
                    f"{device_label} run {idx + 1}/{args.iterations}: timed out, stopping CPU runs.",
                    flush=True,
                )
                break
            if not run_results:
                tail = (
                    "\n".join(raw_output.splitlines()[-5:])
                    if raw_output
                    else "<no output>"
                )
                print(
                    f"{device_label} run {idx + 1}/{args.iterations}: no benchmark output parsed.\n"
                    f"Last output:\n{tail}",
                    flush=True,
                )
                break
            all_runs.append(run_results)
            print(
                f"{device_label} run {idx + 1}/{args.iterations}: parsed {len(run_results)} results (max-len={max_len})",
                flush=True,
            )
        if not all_runs:
            return None
        return average_results(all_runs)

    results_map: Dict[str, Dict[int, BenchResult]] = {}

    if args.device:
        result = run_device(args.device, args.device)
        if result:
            results_map[args.device] = result
        else:
            print(f"No completed runs for device {args.device}.", flush=True)

    if args.device2:
        result = run_device(args.device2, args.device2)
        if result:
            results_map[args.device2] = result
        else:
            print(f"No completed runs for device {args.device2}.", flush=True)

    if not results_map:
        raise SystemExit("No devices selected. Use --device and/or --device2.")

    plot_results(
        results_map,
        out_path,
        title=f"MD5 benchmark (avg of {args.iterations} runs)",
    )

    print(f"Saved plot to {out_path}")


if __name__ == "__main__":
    main()
