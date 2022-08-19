extern crate clap;
extern crate json;

use self::clap::{Arg, App};
use std::fs;

pub mod treenode;

pub fn load_json_tests() -> (json::JsonValue, i32) {
    let matches = App::new("json test loader")
    .version("0.0.1")
    .author("Jean-Christophe Pince <jcpince@gmail.com>")
    .about("Load JSON descriptions of algorithms unit tests.")
    .arg(Arg::with_name("json_unittests")
             .short('j')
             .long("json_unittests")
             .takes_value(true)
             .required(true)
             .help("A json unit tests file"))
    .arg(Arg::with_name("index")
             .short('i')
             .long("index")
             .takes_value(true)
             .help("Run the test specified at index"))
    .get_matches();

    let json_unittests = matches.value_of("json_unittests").unwrap();
    println!("The json unit tests file passed is: {}", json_unittests);

    let test_idx : i32 = matches.value_of("index").unwrap_or("-1").parse().unwrap();

    let data = fs::read_to_string(json_unittests).expect(
                    "Unable to read json unit tests file.");
    match json::parse(&data) {
        Ok(json_dict) => {
            return (json_dict["tests"].clone(), test_idx);
        }
        Err(error) => panic!("Problem parsong the json data in {}: {:?}", json_unittests, error),
    };
}
