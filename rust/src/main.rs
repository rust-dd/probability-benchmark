use rand::SeedableRng;
use rand_distr::{Distribution, Normal};
use std::time::Instant;

const N: usize = 500_000;
const T: f64 = 1.0;
const DT: f64 = T / N as f64;
const THETA: f64 = 1.0;
const MU: f64 = 1.0;
const SIGMA: f64 = 1.0;
const NUM_RUNS: usize = 1000;

fn run_once(rng: &mut rand::rngs::SmallRng) -> u128 {
    let start = Instant::now();

    let mut gn = [0.0; N - 1];
    let normal = Normal::new(0.0, DT.sqrt()).unwrap();

    for i in 0..N - 1 {
        gn[i] = normal.sample(rng);
    }

    let mut ou = [0.0; N];
    for i in 1..N {
        ou[i] = ou[i - 1] + THETA * (MU - ou[i - 1]) * DT + SIGMA * gn[i - 1];
    }
    std::hint::black_box(&ou);

    start.elapsed().as_nanos()
}

fn main() {
    let mut total_ns: u128 = 0;
    let mut rng = rand::rngs::SmallRng::from_rng(&mut rand::rng());

    for _ in 0..NUM_RUNS {
        total_ns += run_once(&mut rng);
    }

    let avg_ns = total_ns / NUM_RUNS as u128;
    println!("Average elapsed time over {} runs: {} ns", NUM_RUNS, avg_ns);
    println!("Total: {} ns", total_ns);
}
