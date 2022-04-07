%%
% ME EN 6240    Assignment 22    Ryan Dalby

% Want to design a ninth-order, low-pass FIR filter with a cutoff frequency
% at 0.2 F_N. Plot both the input and filtered output for a 1000 input
% signal consisting of two equal amplitude sinusoids, one at 0.1 f_N and
% one at 0.5 f_N

fN = 20;

sampFreq = 1000;

bVals = fir1(9, (0.2*fN)/(1000/2), 'low');

disp(bVals)