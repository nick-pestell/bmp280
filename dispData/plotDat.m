dbstop if error
clear all

arduino = serial('COM6');
arduino.InputBufferSize = 1;
arduino.BaudRate = 9600;
try 
    fopen(arduino)
catch err
    fclose(instrfind);
    error('incorect com port')
end

Tmax = 60;
figure
grid on;
xlabel('Time(s)');
Ts = 0.001; i = 0; data = 0; t = 0;

tic;

%% image quality
while toc <= Tmax
    i = i +1;
    data(i) = fread(arduino);
%     timeS(i) = toc;
%     t(i) = toc;
%     if i > 1
%         T = toc - t(i-1);
%         while T <Ts
%             T = toc - t(i-1);
%         end
%     end
    t(i) = toc;
    if i > 1
        axis([toc-5 toc+5 0 255]);
        line([t(i-1) t(i)],[data(i-1) data(i)])
        drawnow
    end


end
save('pressureData.mat','data');



fclose(arduino);
            