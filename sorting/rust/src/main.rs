use rand::Rng;
use std::process::exit;
use std::env::args;
mod bubble;
mod quick;

fn print_array(array: &[i32], msg: &str) -> () {
    print!("~~~~~ {msg}: ");
    print!("[");
    for i in 0..array.len() - 1 {
        print!("{}, ", array[i]);
    };
    print!("{}]\n", array[array.len() - 1]);
}

fn main() {
    let clargs_initial: Vec<String> = args().collect();
    let clargs: Vec<&str> = clargs_initial.iter().map(|s| &**s).collect::<Vec<&str>>().drain(1..).collect();
    let clargs_len = clargs.len();
    assert_ne!(clargs_len, 0, "~~~~~ No arguments have been provided.");

    let mut rng = rand::thread_rng();
    let mut array_to_sort: [i32; 128] = [0; 128];
    let length: usize = array_to_sort.len();
    for i in 0..128 {
        array_to_sort[i] = rng.gen_range(-500..501);
    }

    print_array(&array_to_sort, "Unsorted array");

    for i in 0..clargs_len {
        match clargs[i] {
            "quick" => {
                println!("~~~~~ Runing quicksort.");
                quick::sort(&mut array_to_sort, 0, length - 1);
                print_array(&array_to_sort, "Sorted array");
                break;
            },
            "bubble" => {
                println!("~~~~~ Runing quicksort.");
                bubble::sort(&mut array_to_sort);
                print_array(&array_to_sort, "Sorted array");
                break;
            }
            &_ => { println!("Invalid argument"); exit(1); }
        }
    }
}

