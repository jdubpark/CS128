// Fill out the functions below according to each's specification...

// [COMPLETE THIS FUNCTION - DO NOT MODIFY THE GIVEN FUNCTION SIGNATURE]
pub fn class_number_status(class_number: i32) -> String {
    // Use the given class number to return a String commenting on that course.
    // If the class number is 128, return "the best class". Otherwise, if the course
    // number is in the 100s, return "100 level". Apply this same pattern for 200, 
    // 300, and 400 level courses. If the course is in the 500s, return "grad course". 
    // For any other course number, return "invalid course number".

    if class_number == 128 {
        return "the best class".to_string();
    }
    if 100 <= class_number && class_number < 200 {
        return "100 level".to_string();
    }
    if 200 <= class_number && class_number < 300 {
        return "200 level".to_string();
    }
    if 300 <= class_number && class_number < 400 {
        return "300 level".to_string();
    }
    if 400 <= class_number && class_number < 500 {
        return "400 level".to_string();
    }
    if 500 <= class_number && class_number < 600 {
        return "grad course".to_string();
    }
    return "invalid course number".to_string();
}

// [COMPLETE THIS FUNCTION - DO NOT MODIFY THE GIVEN FUNCTION SIGNATURE]
pub fn return_3_point_5_as_double() -> f64 {
    // return the value 3.5 with double precision

    return 3.5_f64;
}

// [COMPLETE THIS FUNCTION - DO NOT MODIFY THE GIVEN FUNCTION SIGNATURE]
pub fn return_rustacean() -> char {
    // Return the rust crab emoji as a character. HINT: https://emojipedia.org/crab/
    
    return String::from("🦀").chars().next().unwrap(); // 1F980
}

pub fn match_item(item: &str) -> &str {
    let electronics = vec!["computer", "television", "microwave"];
    let food = vec!["banana", "pizza", "bread", "pancake", "spaghetti"];
    let animal = vec!["cat", "elephant", "giraffe", "panda"];
    let movie = vec!["Spiderman", "Interstellar"];
    let person = vec!["Eustis", "Neil", "Welby", "Ferris"];
    if electronics.contains(&item) {
        return "electronics";
    }
    if food.contains(&item) {
        return "food";
    }
    if animal.contains(&item) {
        return "animal";
    }
    if movie.contains(&item) {
        return "movie";
    }
    if person.contains(&item) {
        return "person";
    }
    
    return "invalid item";
}

// TODO: [INSERT LAST FUNCTION HERE]
// Your code will not compile until you have completed this function.

// You can test your code with the test cases we've provided by running `cargo test`
#[cfg(test)]
mod test {
    use super::*;
    
    #[test]
    fn test_class_number_status() {
        // Expected responses for valid course numbers:
        assert_eq!(class_number_status(128), String::from("the best class"));
        assert_eq!(class_number_status(100), String::from("100 level"));
        assert_eq!(class_number_status(196), String::from("100 level"));
        assert_eq!(class_number_status(124), String::from("100 level"));
        assert_eq!(class_number_status(200), String::from("200 level"));
        assert_eq!(class_number_status(299), String::from("200 level"));
        assert_eq!(class_number_status(225), String::from("200 level"));
        assert_eq!(class_number_status(300), String::from("300 level"));
        assert_eq!(class_number_status(399), String::from("300 level"));
        assert_eq!(class_number_status(374), String::from("300 level"));
        assert_eq!(class_number_status(400), String::from("400 level"));
        assert_eq!(class_number_status(499), String::from("400 level"));
        assert_eq!(class_number_status(421), String::from("400 level"));
        assert_eq!(class_number_status(500), String::from("grad course"));
        assert_eq!(class_number_status(573), String::from("grad course"));
        assert_eq!(class_number_status(599), String::from("grad course"));

        // Expected responses for invalid course numbers:
        assert_eq!(class_number_status(0), String::from("invalid course number"));
        assert_eq!(class_number_status(99), String::from("invalid course number"));
        assert_eq!(class_number_status(50), String::from("invalid course number"));

        assert_eq!(class_number_status(600), String::from("invalid course number"));
        assert_eq!(class_number_status(650), String::from("invalid course number"));
        assert_eq!(class_number_status(10000), String::from("invalid course number"));

        assert_eq!(class_number_status(-1), String::from("invalid course number"));
        assert_eq!(class_number_status(-50), String::from("invalid course number"));
        assert_eq!(class_number_status(-100), String::from("invalid course number"));
    }

    #[test]
    fn test_return_3_point_5_as_double() {
        let result: f64 = return_3_point_5_as_double();
        assert_eq!(result, 3.5);
    }

    #[test]
    fn test_return_rustacean() {
        let result: i32 = return_rustacean() as i32;
        assert_eq!(result, 0x1f980);
    }


    #[test]
    fn test_match_item() {
        assert_eq!(match_item("computer"), String::from("electronics"));
        assert_eq!(match_item("television"), String::from("electronics"));
        assert_eq!(match_item("microwave"), String::from("electronics"));
        assert_eq!(match_item("banana"), String::from("food"));
        assert_eq!(match_item("pizza"), String::from("food"));
        assert_eq!(match_item("bread"), String::from("food"));
        assert_eq!(match_item("pancake"), String::from("food"));
        assert_eq!(match_item("spaghetti"), String::from("food"));
        assert_eq!(match_item("cat"), String::from("animal"));
        assert_eq!(match_item("elephant"), String::from("animal"));
        assert_eq!(match_item("giraffe"), String::from("animal"));
        assert_eq!(match_item("panda"), String::from("animal"));
        assert_eq!(match_item("Spiderman"), String::from("movie"));
        assert_eq!(match_item("Interstellar"), String::from("movie"));
        assert_eq!(match_item("Eustis"), String::from("person"));
        assert_eq!(match_item("Neil"), String::from("person"));
        assert_eq!(match_item("Welby"), String::from("person"));
        assert_eq!(match_item("Ferris"), String::from("person"));
        assert_eq!(match_item("Apple"), String::from("invalid item"));
    }
}
