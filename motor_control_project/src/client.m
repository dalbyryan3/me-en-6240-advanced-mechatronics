function client(port)
%   provides a menu for accessing PIC32 motor control functions
%
%   client(port)
%
%   Input Arguments:
%       port - the name of the com port.  This should be the same as what
%               you use in screen or putty in quotes ' '
%
%   Example:
%       client('/dev/ttyUSB0') (Linux/Mac)
%       client('COM3') (PC)
%
%   For convenience, you may want to change this so that the port is hardcoded.
   
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

has_quit = false;
% menu loop
while ~has_quit
    fprintf('PIC32 MOTOR DRIVER INTERFACE\n\n');
    % display the menu options; this list will grow
    % fprintf('     d: Dummy Command    q: Quit\n     x: Add Two Numbers Command');
    fprintf(['     q: Quit     x: Add Two Numbers Command\n     c: Read Encoder (counts)     d: Read Encoder (deg)     e: Reset Encoder\n' ...
        '     a: Read ADC (counts)     b: Read ADC Current Sense Value (mA)     f: Set Signed PWM\n' ...
        '     p: Set mode to IDLE     r: Get current mode']);
    % read the user's choice
    selection = input('\nENTER COMMAND: ', 's');
     
    % send the command to the PIC32
    fprintf(mySerial,'%c\n',selection);
    
    % take the appropriate action
    switch selection
        % case 'd'                         % example operation
        %     n = input('Enter number: '); % get the number to send
        %     fprintf(mySerial, '%d\n',n); % send the number
        %     n = fscanf(mySerial,'%d');   % get the incremented number back
        %     fprintf('Read: %d\n',n);     % print it to the screen
        case 'x'
            % Add two numbers
            n1 = input('Enter the first number to add: ');
            fprintf(mySerial, '%d\n', n1);
            n2 = input('Enter the second number to add: ');
            fprintf(mySerial, '%d\n', n2);
            res = fscanf(mySerial, '%d');
            fprintf('Read: %d\n',res);
        case 'c'
            % Get encoder counts
            counts = fscanf(mySerial, '%d');
            disp(counts)
            fprintf('The motor angle is %d counts.\n', counts)
        case 'e'
            % Reset encoder count to 32768
            fprintf('The encoder counts have been reset to the default value of 32768.\n')
        case 'd'
            % Get encoder counts converted to degrees
            countsDeg = fscanf(mySerial, '%f');
            fprintf('The motor angle is %.2f degrees.\n', countsDeg)
        case 'a'
            % Get adc counts
            adcCounts = fscanf(mySerial, '%d');
            fprintf('The ADC counts are %d counts.\n', adcCounts)
        case 'b'
            % Get adc current sense reading in mA
            adc_mA = fscanf(mySerial, '%f');
            fprintf('The ADC current sense reading is %.2f mA\n.', adc_mA)
        case 'f'
            % Set motor PWM and direction value and set mode to PWM
            pwm_val = input('Enter signed motor PWM value (-100% to 100%):');
            fprintf(mySerial, '%f\n', pwm_val);
        case 'p'
            % Set operating mode to IDLE
            fprintf('Operating mode was set to IDLE.\n');
        case 'r'
            % Get operating mode
            mode = fscanf(mySerial, '%s');
            fprintf('The operating mode is %s.\n', mode);
        case 'q'
            has_quit = true;             % exit client
        otherwise
            fprintf('Invalid Selection %c\n', selection);
        % TODO: Diagnose incoming data formatting issues, encoder and adc
        % readings can be delayed/misformatted, need to handle this
    end
end

end
