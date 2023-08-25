; ModuleID = 'example'
source_filename = "example.bc"

define i32 @fragile_add(i32 %a, i32 %b) {
  %sum = add i32 %a, %b
  ret i32 %sum
}

define i32 @safe_sub(i32 %a, i32 %b) {
  %diff = sub i32 %a, %b
  ret i32 %diff
}

define i32 @fragile_mul(i32 %a, i32 %b) {
  %result = mul i32 %a, %b
  ret i32 %result
}

