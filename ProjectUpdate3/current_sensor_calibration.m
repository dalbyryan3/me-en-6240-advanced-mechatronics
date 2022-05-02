%%
clear
close all
%% 
calibrationVals_counts = [568 574 528 448 512 528 575 560 512 495 415 447 591 471 576 391 464 448 608 607 623 439 415 464 503 512 511];
calibrationVals_mA = [120 120 120 -120 -120 -120 160 160 160 -160 -160 -160 220 220 220 -230 -230 -230 430 430 430 -440 -440 -440 0 0 0];

p = polyfit(calibrationVals_counts, calibrationVals_mA, 1);
m = p(1);
b = p(2);

countVals = linspace(min(calibrationVals_counts), max(calibrationVals_counts), 100);

figure
plot(calibrationVals_counts, calibrationVals_mA, 'rx')
hold on
plot(countVals,m*countVals+b, 'b--');
xlabel('ADC Counts')
ylabel('Measured Current')
title('Current Sensor Calibration')
legend('Measured Values', sprintf('Least-Squares Linear Regression\nm=%.2f, b=%.2f', m, b), location='best')
%%
saveas(gcf,'..\latex\images\current_sensor_calibration_curve.png');