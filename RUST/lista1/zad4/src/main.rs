fn main() {
    println!("Hello, world!");
}

fn printer_error(s: &str) -> String {
    let licznik = s.replace(|ch| ch >='a' && ch <= 'm', "").len();
    format!("{}/{}", licznik, s.len())
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn should_pass_all_the_tests_provided1() {
        assert_eq!(&printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "3/56");
    }

    #[test]
    fn should_pass_all_the_tests_provided2() {
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "6/60");
    }

    #[test]
    fn should_pass_all_the_tests_provided3() {
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyzuuuuu"), "11/65");
    }

    #[test]
    fn should_pass_all_the_tests_provided4() {
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaxxxmmmmmmmmmmmzzzxyzuuuuu"), "17/41");
    }

    #[test]
    fn should_pass_all_the_tests_provided5() {
        assert_eq!(&printer_error("aaaaaaaazzzzbbbb"), "4/16");
    }
}