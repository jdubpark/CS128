#[derive(Debug)]
pub enum Color {
    Blue,
    Orange,
    Red,
    Green,
    Yellow,
    Purple
}

#[derive(Debug)]
pub enum ColorError {
    InvalidColor,
    EmptyColor
}

/// TODO: Implement this function
/// You must return a Result<Color, ColorError> based on the Option<String> passed in
/// There are a number of options for the color so make sure to use a match statement
/// If the color String is invalid (doesn't match with the enum), return an Err(InvalidColor)
/// If the color Stirng is empty, return an Err(EmptyColor)
pub fn color_string_to_enum(color: Option<String>) -> Result<Color, ColorError> {
    if color == None {
        return Err(ColorError::EmptyColor);
    }
    let c = color.unwrap();
    if c.is_empty() {
        return Err(ColorError::EmptyColor);
    }
    return match c.as_str() {
        "blue" => Ok(Color::Blue),
        "orange" => Ok(Color::Orange),
        "red" => Ok(Color::Red),
        "green" => Ok(Color::Green),
        "yellow" => Ok(Color::Yellow),
        "purple" => Ok(Color::Purple),
        "blue" => Ok(Color::Blue),
        _ => Err(ColorError::InvalidColor)
    }
}

/// TODO: Implement this function
/// You must find the Fibonacci sequence of numbers not exceding the number passed in
/// Return the sum of the odd-valued numbers in the sequence as an Option<i32>
/// If the number passed in is less than or equal to 0, return None
pub fn fibonacci_odd_sum(target: i32) -> Option<(i32, i32)> {
    if target <= 0 {
        return None;
    }

    let mut fib_n1 = 1;
    let mut fib_n2 = 1;
    let mut fib = 2;
    let mut sum = 0;
    while fib <= target {
        if fib % 2 != 0 {
            sum += fib;
        }
        fib = fib_n1 + fib_n2;
        fib_n2 = fib_n1;
        fib_n1 = fib;
    }
    return Some((sum+2, fib_n2));
}

// You can test your code with the test cases we've provided by running `cargo test`
// We also encourage you to add more assert statements to test out your code further!
#[cfg(test)]
mod test {
    use super::*;
    
    #[test]
    fn test_color_string_to_enum() {
        assert!(matches!(color_string_to_enum(Some("blue".to_string())), Ok(Color::Blue)));
        assert!(matches!(color_string_to_enum(Some("orange".to_string())), Ok(Color::Orange)));
    }


    #[test]
    fn test_fibonacci_odd_sum() {
        assert_eq!(fibonacci_odd_sum(-21), None);
        
        assert_eq!(fibonacci_odd_sum(185), Some((421, 233)));
        assert_eq!(fibonacci_odd_sum(4904859), Some((4613732, 3524578)));
        assert_eq!(fibonacci_odd_sum(1111111111), Some((1485607536, 701408733)));
    }

}
