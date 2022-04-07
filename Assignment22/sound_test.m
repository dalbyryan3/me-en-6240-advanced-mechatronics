%%
% ME EN 6240    Assignment 22    Ryan Dalby
clear
%%
sampFreq = 8192; % Hz
timeOn = 1; % s
t = 0:1/sampFreq:timeOn;

freq1 = 500; % 1st sound freq
freq2 = 2500; % 2nd sound freq

unfilteredSignal = 0.5 * sin(2*pi*freq1*t) + 0.5*sin(2*pi*freq2*t);


% FIR filter
N = 4;
BLow = fir1(N, 1000/(sampFreq/2), 'low');
BHigh = fir1(N, 2000/(sampFreq/2), 'high');
lowFIR = filter(BLow, 1, unfilteredSignal);
highFIR = filter(BHigh, 1, unfilteredSignal);

titleSize = 12;

sound(unfilteredSignal);
pause(4);
figure
plotFFT(unfilteredSignal)
title('Unfiltered Signal (Constructed of both 500Hz tone and 2500Hz tone)', 'fontsize', titleSize)
ylim([0,0.5])

sound(lowFIR);
pause(4);
figure
plotFFT(lowFIR)
title('Low Pass Filtered Signal (Extracting 500Hz tone)', 'fontsize', titleSize)
ylim([0,0.5])

sound(highFIR);
pause(4);
figure
plotFFT(highFIR);
title('High Pass Filtered Signal (Extracting 2500Hz tone)', 'fontsize', titleSize)
ylim([0,0.5])