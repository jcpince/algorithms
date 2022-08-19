# algorithms

Small algorithm exercises from leetcode, hackerrank...

b __asan_on_error to debug

# Rust
## Add new Leetcode exercise
Edit leetcode/Cargo.toml and add a section as follows:
```yaml
[[bin]]
name = "<new exercise name>"
path = "<new exercise name>.rs"
```

## Build all the examples
```shell
cargo build
```

## Test an exercise
```shell
./target/debug/<exercise name> --json_unittests leetcode/<exercise name>.unittests.json [--index <test idx>]
```