function data=readFromCOM()
data = [];
device = serialport("COM17",115200);
FS = stoploop({'Click OK to stop acquisition'}) ;
disp('> Compile and run the code. If already running, compile and run the code from scratch');
%string = '';

rowNum = 1;
error = false;

time_step = 0.005;  % intervallo di tempo tra i valori
total_time = 0;     % tempo totale trascorso
plot_window = 2;   % durata della finestra di visualizzazione in secondi
speed_values = [];          % array per memorizzare i dati
acc_values = [];          % array per memorizzare i dati
timestamps = [];    % array per memorizzare i timestamp

% Crea la figura e gli assi per il plot
hFig = figure;
screenSize = get(0,'ScreenSize');
set(hFig, 'Units', 'pixels', 'OuterPosition', screenSize);
subplot(2,1,1);
h = plot(nan, nan);
xlabel('Time (s)');
ylabel('Speed (RPM)');
title('Real-Time Speed Plot');
ylim([-150, 150]);
grid on;
hold on;

% Secondo grafico (sotto)
subplot(2, 1, 2);
h2 = plot(nan, nan);
xlabel('Time (s)');
ylabel('Acceleration (RPM/s)');
title('Real-Time Acceleration Plot');
ylim([-3000, 3000]);
grid on;
hold on;



%wait for INIT
while(~FS.Stop())
    newLineString = readline(device);
    if(isequal(strtrim(newLineString),"INIT"))
        break;
    end
end

tempo=0;
while(~FS.Stop())
    newLineString = readline(device);
    if(not(isequal(strtrim(newLineString),"INIT")))
        newStr = split(newLineString,', ');
        for j=1:length(newStr)
            numValue = str2double(strtrim(newStr(j)));
            if isnan(numValue)
               error = true; 
            end
            data(rowNum,j) = numValue;
        end
        if error
            disp(strcat('Expected numeric value, but read the following value: ',strtrim(newStr(j))));
            break;
        end   

    total_time = total_time + time_step;

    % Aggiorna gli array di dati
    speed_values = [speed_values, data(rowNum,1)];
    acc_values = [acc_values, data(rowNum,2)];
    timestamps = [timestamps, total_time];
    
    
    
    % Determina i limiti della finestra di visualizzazione
    if total_time <= plot_window
        x_min = 0;
        x_max = plot_window;
    else
        x_min = total_time - plot_window;
        x_max = total_time;
    end
    
    tempo = tempo + 1;
    if(tempo >= 20)
        % Aggiorna il plot
        subplot(2,1,1);
        set(h, 'XData', timestamps, 'YData', speed_values);
        xlim([x_min, x_max]);
        ylim([-150, 150]);
        subplot(2,1,2);
        set(h2, 'XData', timestamps, 'YData', acc_values);
        xlim([x_min, x_max]);
        ylim([-3000, 3000]);
        drawnow;
        tempo = 0;
    end

    end
end

FS.Clear() ;
clear FS ;
clear device;
end
