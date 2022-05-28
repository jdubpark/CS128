extern crate calculator;

use text_io::read;

fn main() {
    let num = calculator::solve_all("equations.txt").unwrap();
    println!("Equation file solved: {:?}", num);
    println!("🧮 Please enter an equation. Enter 'done' to exit the program.");
    let mut line: String = read!("{}\n");

    while line != "done" {
        println!("Solution: {:?}", calculator::solve(&line).unwrap());

        println!("🧮 Please enter an equation. Enter 'done' to exit the program.");
        line = read!("{}\n");
    }
}