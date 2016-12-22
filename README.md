# iGenfuner
Imaginer-Generate-function-er =>(iGenfuner)  : Function generator and parser

- From this class name,you can know this a utils for Imaginer,It's use to parser(use RPN) a input string, maybe a math function or a math expression;
- From the parser result,must Generate a operate stream (op-stream), to save/record the function or expression Each step of the process;
- Then while you want to get a Special value(eg:1,2,3...),Will use the recorded op-stream, step-by-step calculation until the final results
