fn main() {
    println!("Hello, world!");
}

fn count_bits(n: i64) -> u32 {
    let count: u32 = n.count_ones();
    return count;
}

#[cfg(test)]
mod tests {
    use super::*;

    fn do_test(n: i64, expected: u32) {
        let actual = count_bits(n);
        assert_eq!(actual, expected,
            "expected {} but got {} for n = {}",
            expected, actual, n
        );
    }

    #[test]
    fn sample_tests1() {
        do_test(4, 1);
    }
    #[test]
    fn sample_tests2() {
        do_test(0, 0);
    }

    #[test]
    fn sample_tests3() {
        do_test(7, 3);
    }

    #[test]
    fn sample_tests4() {
        do_test(77231418, 14);
    }

    #[test]
    fn sample_tests5() {
        do_test(i64::MAX, 63)
    }
}
