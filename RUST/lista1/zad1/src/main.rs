fn main() {
    println!("Hello, world!");
}

fn string_to_number(s: &str) -> i32 {
    let liczba: i32 = s.parse().unwrap();
    return liczba;
}

#[cfg(test)]
mod tests {
    use super::string_to_number;
    use rand::prelude::*;

    #[test]
    fn returns_expected1() {
      assert_eq!(string_to_number("1234"), 1234);
    }

    #[test]
    fn returns_expected2() {
      assert_eq!(string_to_number("123"), 123);
    }
    #[test]
    fn returns_expected3() {
      assert_eq!(string_to_number("0"), 0);
    }
    #[test]
    fn returns_expected4() {
      assert_eq!(string_to_number("-1234"), -1234);
    }
    #[test]
    fn returns_expected5() {
      assert_eq!(string_to_number("14"), 14);
    }


    #[test]
    fn works_on_random() {
        let mut rng = thread_rng();
        for _ in 0..5 {
            let num : i32 = rng.gen();
            let input = num.to_string();
            assert_eq!(string_to_number(&input), num);
        }        
    }
}