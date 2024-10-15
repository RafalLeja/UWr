fn main() {
    println!("Hello, world!");
}

fn longest(a1: &str, a2: &str) -> String {
    let binding = a1.to_owned() + a2;
    let mut out = binding.split("").collect::<Vec<_>>();
    out.sort();
    out.dedup();
    out.join("")
}

#[cfg(test)]
    mod tests {
    use super::*;
   
    fn testing(s1: &str, s2: &str, exp: &str) -> () {
        println!("s1:{:?} s2:{:?}", s1, s2);
        println!("{:?} {:?}", longest(s1, s2), exp);
        println!("{}", longest(s1, s2) == exp);
        assert_eq!(&longest(s1, s2), exp)
    }

    #[test]
    fn basic_tests1() {
        testing("aretheyhere", "yestheyarehere", "aehrsty");
    }

    #[test]
    fn basic_tests2() {
        testing("loopingisfunbutdangerous", "lessdangerousthancoding", "abcdefghilnoprstu");
    }

    #[test]
    fn basic_tests3() {
        testing("abc", "def", "abcdef");
    }

    #[test]
    fn basic_tests4() {
        testing("aaabcijkk", "bdef", "abcdefijk");
    }

    #[test]
    fn basic_tests5() {
        testing("aaaaaxxxxxxx", "bbbbzzzz", "abxz");
    }
}
