# 🦀 Probability Benchmark: Rust vs Zig vs C

This repository benchmarks three languages — **Rust**, **Zig**, and **C** — for generating Ornstein–Uhlenbeck (OU) stochastic processes, commonly used in stochastic calculus and mathematical finance.

## 💡 What is it about?

We simulate **1,000 trajectories**, each of length **500,000**, using a simple Euler scheme. Each trajectory uses normally distributed increments to generate a mean-reverting process.

Mathematically, the OU process is given by:

\[
dX_t = \theta (\mu - X_t)\,dt + \sigma\,dW_t
\]

where:
- \(\theta\) = mean reversion speed
- \(\mu\) = long-term mean
- \(\sigma\) = volatility
- \(dW_t\) = standard Brownian motion increment

---

## ⚡ Motivation

As the maintainer of [stochastic-rs](https://github.com/dancixx/stochastic-rs), I'm a big fan of low-level, hardware-oriented programming languages, especially for scientific computing.

I’m not an expert in Zig or C, so this benchmark represents what might happen if a "regular Rust user" tries to quickly hack together similar code in other languages after a bit of Googling and reading docs.

---

## 💻 Code snippets

### Rust (🦀)

- Uses `rand` and `rand_distr`
- Run with: `cargo run --release`

[See code here](./rust_version.rs)

---

### Zig (⚡)

- Uses [zprob](https://github.com/pblischak/zprob)
- Run with: `zig build run -Doptimize=ReleaseFast`

[See code here](./zig_version.zig)

---

### C (👴)

- Simple Box-Muller method for normal sampling
- Compile with: `gcc -O3 -march=native -o main main.c -lm`

[See code here](./c_version.c)

---

## 📊 Results

| Language | Avg (ns)    | Total (ns)              |
|-----------|-------------|------------------------|
| **Rust** 🦀 | 68 ns    | 68,014 ns          |
| **Zig** ⚡ | 3,583,649 ns | 3,583,649,726 ns (~3 sec) |
| **C** 👴  | 3,611,471 ns | 3,611,471,000 ns (~3 sec) |

Rust turned out to be significantly faster in this experiment, even though it was the language I’m most familiar with — proving that strong ergonomics and high performance can go hand-in-hand.

---

## 🗣️ Discussion

This benchmark is not intended to be a definitive performance proof, but rather a fun exploration. Contributions, improvements, or corrections are highly welcome!

👉 [Join the discussion](https://github.com/rust-dd/probability-benchmark/discussions/1)

---

## 📎 License

MIT

---

**Enjoy, and happy benchmarking! 🚀**
