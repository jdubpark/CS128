use std::fs;
// use std::fs::File;
// use std::io::prelude::*;
// use std::io::BufReader;

use rand::Rng;

#[derive(Debug, Copy, Clone)]
pub enum Operation {
    Add,
    Subtract,
    Multiply,
    Divide,
    Modulo
}

impl Operation {
    pub fn from_char(symbol: char) -> Option<Operation> {
        return match symbol {
            '+' => Some(Operation::Add),
            '-' => Some(Operation::Subtract),
            'x' => Some(Operation::Multiply),
            '*' => Some(Operation::Multiply),
            '/' => Some(Operation::Divide),
            '%' => Some(Operation::Modulo),
            _ => None
        }
    }
}

// [HELPER FUNCTION - DO NOT EDIT]
pub fn get_equation_tuple(line: &String) -> (Option<&str>, Option<&str>) {
    let v: Vec<&str> = line.split(&['-', '+', 'x', '*', '/', '%'][..]).collect();
    let x: Option<&str> = match v.get(0) {
        Some(x) => Some(x),
        None => None
    };
    let y: Option<&str> = match v.get(1) {
        Some(y) => Some(y),
        None => None
    };
    (x, y)
}

pub fn parse_equation(line: &String) -> Result<(f32, f32, Operation), ()> {
    match get_equation_tuple(line) {
        (Some(xm), Some(ym)) => {
            let x = xm.trim();
            let y = ym.trim();

            if x == "" || y == "" {
                return Err(());
            }

            let v = line.replace(x, "").replace(y, "").trim().chars().next().unwrap();
            let op = Operation::from_char(v);
            println!("x: {}", x);
            println!("y: {}", y);
            println!("v: {}", v);
            println!("op: {}", op.is_none());

            if op.is_none() {
                return Err(());
            }
            
            Ok((
                x.parse::<f32>().unwrap(),
                y.parse::<f32>().unwrap(),
                op.unwrap()
            ))
        },
        // covers (None, None), (None, Some(_)), (Some(_), None)
        _ => Err(()), // if None, panic without any message
    }
}

pub fn solve(equation: &String) -> Result<f32, ()> {
    let eq = parse_equation(equation);
    return match eq {
        Ok((x, y, op)) => match op {
            Operation::Add => Ok(x + y),
            Operation::Subtract => Ok(x - y),
            Operation::Multiply => Ok(x * y),
            Operation::Divide => Ok(x / y),
            Operation::Modulo => Ok(x % y),
        },
        Err(_e) => Err(())
    }
}

pub fn solve_all(file_path: &str) -> Result<f32, ()> {
    let data = fs::read(file_path).expect("Unable to read file");
    Ok(0.3)
}


#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test_solve_single_number() {
        for i in -20..20 {
            assert!(solve(&i.to_string()).is_err());
        }
    }

    #[test]
    fn test_solve_two_random_numbers() {
        let mut rng = rand::thread_rng();

        for _ in 0..200 {
            let (xi, yi): (i16, i16) = rng.gen();
            let (x, y): (f32, f32) = (xi.abs() as f32, yi.abs() as f32); // avoid int overflow by upcasting to int with more space

            assert_eq!(solve(&format!("{}+{}", x, y)).unwrap(), x + y);
            assert_eq!(solve(&format!("{}-{}", x, y)).unwrap(), x - y);
            assert_eq!(solve(&format!("{}x{}", x, y)).unwrap(), x * y);
            assert_eq!(solve(&format!("{}*{}", x, y)).unwrap(), x * y);
            assert_eq!(solve(&format!("{}%{}", x, y)).unwrap(), x % y);
            assert_eq!(solve(&format!("{}/{}", x, y)).unwrap(), x / y);
        }
    }
}