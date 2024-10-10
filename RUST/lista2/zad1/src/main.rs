fn main() {
    println!("Hello, world!");
}

fn get_count(string: &str) -> usize {
    let vowels = vec!['a', 'e', 'i', 'o', 'u'];
    let vowels_count: usize = string.chars().filter(|l| vowels.contains(&l)).count();
    // Do your magic here
    
    vowels_count
  }
  

#[test]
fn my_tests1() {
  assert_eq!(get_count("abracadabra"), 5);
}

#[test]
fn my_tests2() {
  assert_eq!(get_count("abracdbr"), 2);
}

#[test]
fn my_tests3() {
  assert_eq!(get_count("aeiou"), 5);
}

#[test]
fn my_tests4() {
  assert_eq!(get_count("a b c d e"), 2);
}

#[test]
fn my_tests5() {
  assert_eq!(get_count("bbbbbbb"), 0);
}