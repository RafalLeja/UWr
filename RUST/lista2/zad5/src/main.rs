fn main() {
    println!("Hello, world!");
}

fn gimme_the_letters(sp: &str) -> String {
    let a: u8 = sp.chars().nth(0).unwrap() as u8;
    let b: u8= sp.chars().nth(2).unwrap() as u8;
    (a..=b).map(|i| char::from(i)).collect()
}

// Add your tests here.
// See https://doc.rust-lang.org/stable/rust-by-example/testing/unit_testing.html

#[cfg(test)]
mod tests {
    use super::gimme_the_letters;
        
    fn dotest(sp: &str, expected: &str) {
        let actual = gimme_the_letters(sp);
        assert!(actual == expected, 
            "With sp = \"{sp}\"\nExpected \"{expected}\" but got \"{actual}\"")
    }

    #[test]
    fn fixed_tests1() {
        dotest("a-z", "abcdefghijklmnopqrstuvwxyz");
    }

    #[test]
    fn fixed_tests2() {
        dotest("h-o", "hijklmno");
    }

    #[test]
    fn fixed_tests3() {
        dotest("Q-Z", "QRSTUVWXYZ");
    }

    #[test]
    fn fixed_tests4() {
        dotest("J-J", "J");
    }

    #[test]
    fn fixed_tests5() {
        dotest("a-b", "ab");
        dotest("A-A", "A");
        dotest("g-i", "ghi");
        dotest("H-I", "HI");
        dotest("y-z", "yz");
        dotest("e-k", "efghijk");
        dotest("a-q", "abcdefghijklmnopq");
        dotest("F-O", "FGHIJKLMNO");
    }
}
