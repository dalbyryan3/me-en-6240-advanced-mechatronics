% ME EN 6240    Assignment 22    Ryan Dalby

port = 'COM3';

% Opening COM connection
if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end

fprintf('Opening port %s....\n',port);

% settings for opening the serial port. baud rate 230400, hardware flow control
% wait up to 120 seconds for data before timing out
mySerial = serial(port, 'BaudRate', 230400, 'FlowControl', 'hardware','Timeout',120); 
% opens serial connection
fopen(mySerial);
% closes serial port when function exits
clean = onCleanup(@()fclose(mySerial));                                 

unfilteredSignal = [];
filteredSignal = [];

fprintf('Reading unfiltered signal (column1), and FIR filtered signal (column2) from PIC32\n\n');
% Read initial line from PIC
fscanf(mySerial, "%s")
while true
    str = fscanf(mySerial, "%s");
    if str == "END"
        break
    end
    disp(str)
    strSplit =  str2double(split(str, ','));
    unfilteredSignal(end+1) = double(strSplit(1));
    filteredSignal(end+1) = double(strSplit(2));
end

tVals = linspace(0,1,1000);

figure
plot(tVals, unfilteredSignal);
title('Unfiltered Signal');
xlabel('Time(s)');
ylabel('Value');
xlim([0,1]);
ylim([-1,1]);

figure
plot(tVals, filteredSignal);
title('FIR Filtered Signal')
xlabel('Time(s)');
ylabel('Value');
xlim([0,1]);
ylim([-1,1]);

figure
plot(tVals, unfilteredSignal);
hold on
plot(tVals, filteredSignal);
title('Unfiltered and FIR Filtered Signal')
xlabel('Time(s)');
ylabel('Value');
legend('Unfiltered','Filtered')
xlim([0,1]);
ylim([-1,1]);