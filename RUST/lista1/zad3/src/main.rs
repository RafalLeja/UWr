fn main() {
    println!("Hello, world!");
}

fn square_area_to_circle(size:f64) -> f64 {
    size*std::f64::consts::PI/4.0    
}

fn assert_close(a:f64, b:f64, epsilon:f64) {
    assert!( (a-b).abs() < epsilon, "Expected: {}, got: {}",b,a);
}

#[test]
fn returns_expected1() {
  assert_close(square_area_to_circle(9.0), 7.0685834705770345, 1e-8);
}

#[test]
fn returns_expected2() {
    assert_close(square_area_to_circle(20.0), 15.70796326794897, 1e-8);
  }

#[test]
fn returns_expected3() {
    assert_close(square_area_to_circle(5.0), 3.92699082, 1e-8);
}

#[test]
fn returns_expected4() {
assert_close(square_area_to_circle(10.0), 7.85398163, 1e-8);
}

#[test]
fn returns_expected5() {
    assert_close(square_area_to_circle(100.0), 78.53981633, 1e-8);
}