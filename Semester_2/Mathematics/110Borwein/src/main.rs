mod borwein_function;
mod calc_loop;
mod test;

use crate::calc_loop::math::math;
use std::{env, process, f64::consts::FRAC_PI_2};

fn main() {
    let args: Vec<String> = env::args().collect();
    let n: u16;
    let mut array: [f64; 3] = [0.0; 3];

    if args.len() != 2 {
        process::exit(84);
    }
    n = args[1].parse::<u16>().unwrap_or_else(|_| process::exit(84));
    array = math(n, array, 4999.5, 5000.0);
    println!("Midpoint:\nI{} = {:.10}\ndiff = {:.10}\n", n, array[0], (array[0] - FRAC_PI_2).abs());
    println!("Trapezoidal:\nI{} = {:.10}\ndiff = {:.10}\n", n, array[2], (array[2] - FRAC_PI_2).abs());
    println!("Simpson:\nI{} = {:.10}\ndiff = {:.10}", n, array[1], (array[1] - FRAC_PI_2).abs());
    process::exit(0);
}
