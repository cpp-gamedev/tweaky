# tweaky

**Super basic framework for tweaking numeric values at runtime**

## What?

It's often desirable to inspect and tweak gameplay variables using an editor. This library offers a generic framework to do that, and uses JSON for persistence.

## How does it work?

There are two components in the system:
1. `tweaky` database
1. `tweaky` values

The database is a map that associates IDs (`std::string`) to `tweaky::Data`s (int or float values and ranges). A `Value` is a "pointer" to such an entry in the map, initialized by its ID. The intended usage is the following:

1. Store `Value`s instead of numeric types where inspection / tweaking of the value is desired.
1. Populate the database via code and / or a JSON file before any code using `Value`s runs.

All `Value`s will then reflect their corresponding values in the database, and modification of any value will trigger the database to save the entries to the JSON file (if loaded / created successfully before).

## Example

See [whackx](whackx/whackx/game.cpp)
