fn main() {
    println!("Hello, world!");
}

fn count_red_beads(n: u32) -> u32 {
    if n < 2 {
        0
    }else{
        (n-1)*2
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test1() {
      assert_eq!(count_red_beads(0), 0, "count_red_beads(0)");
    }

    #[test]
    fn test2() {
      assert_eq!(count_red_beads(1), 0, "count_red_beads(1)");
    }

    #[test]
    fn test3() {
      assert_eq!(count_red_beads(3), 4, "count_red_beads(3)");
    }

    #[test]
    fn test4() {
      assert_eq!(count_red_beads(5), 8, "count_red_beads(5)");
    }

    #[test]
    fn test5() {
      assert_eq!(count_red_beads(4), 6, "count_red_beads(5)");
    }
}