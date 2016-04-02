
#General Turing Machine

Can translate and recognize. Use xxx.json to hold the formal descrition.



Example formal description to invert binary bits (0 > 1, 1 > 0)

(data/struct.json)
```json
{
    "states": ["S0", "S1", "S2"], // set of states
    "initial": "S0",              // inital state
    "symbols": ["0", "1"],        // set of symbols on tape
    "finals": ["S2"],             // set of finals states 
    "blank": "B",                 // blank symbol (indicate end of the word on tape)
    "start": "<",                 // start symbol (indicate start of the word on tape)
    
    
    "transitions": {              // transition function (main structure of turing machine)
    
    // (state): {(on tape): [(next_state, 2write, direction)], ...}
        "S0": {"0": ["S0", "1", "R"],
               "1": ["S0", "0", "R"],
               "B": ["S1", "B", "L"]
        },
        "S1": {"0": ["S1", "0", "L"],
               "1": ["S1", "1", "L"],
               "<": ["S2", "<", "R"]
        
        },
        // S2 is a final state so {} has nothing
        "S2": {
        }
    }
}
```
--

##To build local

```sh
git clone https://github.com/alexaleluia12/turing-machine.git
cd turing-machine
mkdir bin
make
```
--
##To use

Copy the data/struct.json and update with the values of your turing machine automaton

Run<br/>
``` ./bin/main tape_word path_json_file ```

Return<br />
"Boolean:Output_word"

Example<br />
```sh
./bin/main 0101 data/struct.json
True:1010
```




