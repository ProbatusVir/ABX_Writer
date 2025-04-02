use std::fs;
fn main() {
	let cmdline_args : Vec<String>= std::env::args().collect();
	// Check arguments
	if cmdline_args.len() < 2
	{
		panic!("Expected a file as an argument!");
	}
	else if cmdline_args.len() > 2
	{
		panic!("Too many arguments!");
	}
	// Do the rest
	let arg1 = &cmdline_args[1];
	println!("{arg1}");
	let file_contents = String::from_utf8(fs::read(&cmdline_args[1]).unwrap()).unwrap();
	println!("{file_contents}");

}
