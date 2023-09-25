use rand::Rng;
mod bubble;

fn main() {
    let mut rng = rand::thread_rng();
    let mut array_to_sort: [i32; 128] = [0; 128];
    for i in 0..128 {
        array_to_sort[i] = rng.gen_range(-500..501);
    }

    bubble::sort(&mut array_to_sort);
}
