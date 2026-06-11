pub mod math {

    use crate::borwein_function::borwein;

    pub fn math(n: u16, mut array: [f64; 3], a: f64, b: f64) -> [f64; 3] {
        if a < 0.0 {
            return array
        }
        array[0] += (b - a) * borwein::borwein_math(n, (a + b) / 2.0);
        array[1] += (borwein::borwein_math(n, a) + 4.0 * borwein::borwein_math(n, (a + b) / 2.0) + borwein::borwein_math(n, b)) * ((b - a) / 6.0);
        array[2] += (b - a) / 2.0 * (borwein::borwein_math(n, a) + borwein::borwein_math(n, b));
        math(n, array, a - 0.5, b - 0.5)
    }
}
