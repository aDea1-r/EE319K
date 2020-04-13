str = """
	//{5}
	states[{0}].motorOutput = {1};
	states[{0}].pumpOutput = {6};
	states[{0}].delay = state_delay;
	states[{0}].output[0][0] = &states[{2}];
	states[{0}].output[0][1] = &states[{3}];
	states[{0}].output[1][0] = &states[{4}];
	states[{0}].output[1][1] = &states[{3}];"""
	#0: stateNum, 1:motorStep 2:noPressState 3:WashState 4:continueState
dsc = "state: washer{0}, counting {1}, cycle {2}, currentStep {3}" 
    #0: washer, 1: up/down, 2:cycleNum, 3:current output
	
i = 0
step = 2**(i%5)
comment = dsc.format("Off", "Inflection", (i//5)+1, step )
print(str.format(i, step, i, i+19, i+1,  comment, 0 ))
#0: stateNum, 1:motorStep 2:noPressState 3:WashState 4:continueState
	
for i in range(1,9):
    step = 2**(i%5)
    comment = dsc.format("Off", "Up", (i//5)+1, step )
    print(str.format(i, step, 18-i, i+19, i+1,  comment, 0 ))
    #0: stateNum, 1:motorStep 2:noPressState 3:WashState 4:continueState
    
i = 9
step = 2**(i%5)
comment = dsc.format("Off", "Inflection", (i//5)+1, step )
print(str.format(i, step, i+1, i+19, i+1,  comment, 0 ))
#0: stateNum, 1:motorStep 2:noPressState 3:WashState 4:continueState

for i in range(10,17):
    step = 2**((18-i)%5)
    comment = dsc.format("Off", "Down", (i//5)+1, step )
    print(str.format(i, step, i+1, i+19, i+1,  comment , 0))
    #0: stateNum, 1:motorStep 2:noPressState 3:WashState 4:continueState
    
i=17 
step = 2**((18-i)%5)
comment = dsc.format("Off", "Down", (i//5)+1, step )
print(str.format(i, step, 0, 18, 0,  comment, 0 ))
#0: stateNum, 1:motorStep 2:noPressState 3:WashState 4:continueState
    
i=18
step = 2**( (i-18) %5)
comment = dsc.format("On", "Up", ( (i-18) //5)+1, step )
print(str.format(i, step, 0, i+1, i-17,  comment, i%2 ))
#0: stateNum, 1:motorStep 2:noPressState 3:WashState 4:continueState

for i in range(19,27):
    step = 2**( (i-18) %5)
    comment = dsc.format("On", "Up", ( (i-18) //5)+1, step )
    print(str.format(i, step, 35-i, i+1, i-17,  comment,i%2 ))
    #0: stateNum, 1:motorStep 2:noPressState 3:WashState 4:continueState

i=27
step = 2**( (i-18) %5)
comment = dsc.format("On", "Inflection", ( (i-18) //5)+1, step )
print(str.format(i, step, i-17, i+1, i-17,  comment,i%2 ))
#0: stateNum, 1:motorStep 2:noPressState 3:WashState 4:continueState

for i in range(28,35):
    step = 2**((36-i)%5)
    comment = dsc.format("On", "Down", ( (i-18) //5)+1, step )
    print(str.format(i, step, i-17, i+1, i-17,  comment ,i%2))
    #0: stateNum, 1:motorStep 2:noPressState 3:WashState 4:continueState
    
i=35
step = 2**((36-i)%5)
comment = dsc.format("On", "Down", ((i-18)//5)+1, step )
print(str.format(i, step, 0, 18, 0,  comment,i%2 ))
#0: stateNum, 1:motorStep 2:noPressState 3:WashState 4:continueState
    