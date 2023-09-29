### stem is a state machine
> steam expans state machine which is used to evaluate state maps
> __state map__ is a 2d map of stateQ
> __stateQ__ is a queue of states
> action on state is either use-type of select-type
> use-type action means perfomeing a atomic action based on selected states
> select-type state means selecting a state for performing actions


#### steam code is a low-high level language written in c++
> it has a concept of _cells_
> __cells__ is a multi-variable has number of phases
> 
state map is a 2d ma contains a state buffers in cell and a sequence to evaulate them
maps are created in **stem code** which is kinda like a programming lang 

# stem code dont use parser (its a grammar less lang)
# stem is named after state machine

stem code first comverted to maps whcih are stored in binary files
which then ise used my state machine/engine to evalulte the maps

# progamming in c++
