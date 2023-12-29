### stem is a state machine
> **steam** expands state machine which is used to evaluate state maps

> __state map__ is a 2d map of stateQ

> __stateQ__ is a queue of states

> action on states are either _**use-type**_ of __select-type__

> __use-type__ action means perfomeing a atomic action based on selected states

> __select-type__ state means selecting a state for performing actions


#### steam code is a low-high level language written in c++
> it has a concept of __cells__

> __cells__ is a multi-variable has number of __phases__

__phase__ are like "types" 

* float
* interger
* string
* refernce

### **map** is the fundamental block which is written in this code
* i.e maps are what hold cells 
* operation on cells
* hooks to other maps
* inclusions of libs

###### different maps are connected by **_hooks_**
> __hooks__ can be conditional and un-conditional

##### **keys** :  second to none but map, keys are of prime importance.
* they handle all the basic operation like arithmatics, comparison, selection
* they are also responsible for **data tranfer** b/w maps

##### there are two types of keys
* dependent keys - used with the cell and **feeder**
* independent keys - used only with the cell

> __feeder__ is a another type of action based state which takes data and based on the __dependent key__ use it to either move, transform... etc.


##### stem code dont use parser (its a grammar less lang)
* because it uses limited states -we dont call it state machine for nothing.

### some examples
* #### how to make a loop
* source code
* <img src="https://github.com/green-gray-gaurav/STEM----STATE-MACHINE/blob/master/Screenshot%202023-12-29%20220159.png">
* output
* <img src="https://github.com/green-gray-gaurav/STEM----STATE-MACHINE/blob/master/Screenshot%202023-12-29%20220817.png">

* #### using hooks
* source code
* ![source](https://github.com/green-gray-gaurav/STEM----STATE-MACHINE/blob/master/Screenshot%202023-12-29%20221646.png)
* output
* ![output](https://github.com/green-gray-gaurav/STEM----STATE-MACHINE/blob/master/Screenshot%202023-12-29%20221723.png)
  


* #### a simple program using cells
* source code
* ![SOURCE](https://github.com/green-gray-gaurav/STEM----STATE-MACHINE/blob/master/Screenshot%202023-12-29%20223537.png)
* output
* ![output](https://github.com/green-gray-gaurav/STEM----STATE-MACHINE/blob/master/Screenshot%202023-12-29%20220556.png)




