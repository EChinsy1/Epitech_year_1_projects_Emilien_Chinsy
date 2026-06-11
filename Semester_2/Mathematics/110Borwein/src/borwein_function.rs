pub mod borwein {
    pub fn borwein_math(num: u16, x: f64) -> f64 {
        if x == 0.0 {
            return 1.0
        }
        if num == 0 {
            return ((x / (2.0 * num as f64 + 1.0)).sin()) / (x / (2.0 * num as f64 + 1.0))
        }
        ((x / (2.0 * num as f64 + 1.0)).sin()) / (x / (2.0 * num as f64 + 1.0)) *
        borwein_math(num - 1, x)
    }
}
