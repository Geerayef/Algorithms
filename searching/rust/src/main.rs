use std::env::args;
mod binary;

fn handle_cli_args(mut args: Vec<&str>) {
    let clargs_len = args.len();
    assert_ne!(clargs_len, 0, "~~~~~ No arguments have been provided.");

    for i in 0..clargs_len {
        match args[i] {
            "search" => {
                assert!(i+2 <= clargs_len, "~~~~~ [ERROR]: Invalid number of arguments.\n
                    Program received {clargs_len} arguments, expected at least 3.\n
                    Flag search accepts 2 arguments: 1) Search algorithm name & 2) Element to search for");
                let search_args = args.drain(i+1..=i+2).collect();
                parse_search_args(search_args);
                break;
            },
            &_ => todo!(),
        }
    }
}

fn parse_search_args(args: Vec<&str>) {
    let search_algorithm: String = args[0].into();
    let value_to_find: f32 = args[1].parse().unwrap();
    call(search_algorithm, value_to_find);
}

fn call(algorithm: String, wanted_value: f32) {
    if algorithm == "binary" {
        let mut number_arr: [f32; 128] = [1.0; 128];
        for i in 1..=127 {
            number_arr[i] = number_arr[i - 1] + 2.0 * 2.0;
        }

        binary::search(&number_arr, wanted_value);
    }
}

fn main() {
    let clargs_initial: Vec<String> = args().collect();
    let mut clargs: Vec<&str> = clargs_initial.iter().map(|s| &**s).collect();
    clargs = clargs.drain(1..).collect();
    handle_cli_args(clargs);
}
