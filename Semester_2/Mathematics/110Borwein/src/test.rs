#[cfg(test)]
mod tests {
    use crate::calc_loop::math::math;

    #[test]
    fn test_midpoint_n_eq_0() {
        let mut array: [f64; 3] = [0.0; 3];
        array = math(0, array, 4999.5, 5000.0);
        assert_eq!(array[0], 1.5707651076230331);
    }

    #[test]
    fn test_trapezoid_n_eq_0() {
        let mut array: [f64; 3] = [0.0; 3];
        array = math(0, array, 4999.5, 5000.0);
        assert_eq!(array[1], 1.5707654319558468);
    }

    #[test]
    fn test_simpson_n_eq_0() {
        let mut array: [f64; 3] = [0.0; 3];
        array = math(0, array, 4999.5, 5000.0);
        assert_eq!(array[2], 1.570766080621474);
    }

    #[test]
    fn test_midpoint_n_eq_1000() {
        let mut array: [f64; 3] = [0.0; 3];
        array = math(1000, array, 4999.5, 5000.0);
        assert_eq!(array[0], 1.570762021426856);
    }

    #[test]
    fn test_trapezoid_n_eq_1000() {
        let mut array: [f64; 3] = [0.0; 3];
        array = math(1000, array, 4999.5, 5000.0);
        assert_eq!(array[1], 1.570762021426856);
    }

    #[test]
    fn test_simpson_n_eq_1000() {
        let mut array: [f64; 3] = [0.0; 3];
        array = math(1000, array, 4999.5, 5000.0);
        assert_eq!(array[2], 1.570762021426856);
    }
}
