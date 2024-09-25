function data=readFromCOM()
data = [];
device = serialport("COM10",115200);
FS = stoploop({'Click OK to stop acquisition'}) ;
disp('> Compile and run the code. If already running, compile and run the code from scratch');
%string = '';

rowNum = 1;
error = false;

time_step = 0.045;  % intervallo di tempo tra i valori
total_time = 0;     % tempo totale trascorso
plot_window = 2;   % durata della finestra di visualizzazione in secondi
ASX_U = [];          % array per memorizzare i dati
ASX_Y = [];
ADX_U = [];          % array per memorizzare i dati
ADX_Y = [];
PSX_U = [];          % array per memorizzare i dati
PSX_Y = [];
PDX_U = [];          % array per memorizzare i dati
PDX_Y = [];
acc_values = [];          % array per memorizzare i dati
timestamps = [];    % array per memorizzare i timestamp

% Crea la figura e gli assi per il plot
hFig = figure;
%screenSize = get(0,'ScreenSize');
%set(hFig, 'Units', 'pixels', 'OuterPosition', screenSize);
subplot(2,1,1);
h = plot(nan, nan);
xlabel('Time (s)');
ylabel('U (V)');
title('Real-Time U Plot');
ylim([-150, 150]);
grid on;
hold on;

% Secondo grafico (sotto)
subplot(2, 1, 2);
h2 = plot(nan, nan);
xlabel('Time (s)');
ylabel('Speed (RPM)');
title('Real-Time Speed Plot');
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
               
        % Estrazione dei valori usando espressioni regolari
        t_value = regexp(newLineString, 'T{([^}]+)}', 'tokens');
        asx_values = regexp(newLineString, 'ASX{([^}]+)}', 'tokens');
        adx_values = regexp(newLineString, 'ADX{([^}]+)}', 'tokens');
        psx_values = regexp(newLineString, 'PSX{([^}]+)}', 'tokens');
        pdx_values = regexp(newLineString, 'PDX{([^}]+)}', 'tokens');
        
        % Conversione dei valori da stringhe a numeri
        timestamp = str2double(t_value{1}{1});
        asx = str2double(split(asx_values{1}{1}, ','));
        adx = str2double(split(adx_values{1}{1}, ','));
        psx = str2double(split(psx_values{1}{1}, ','));
        pdx = str2double(split(pdx_values{1}{1}, ','));
        
        % Assegnazione dei valori a variabili separate
        ASX_U = [ASX_U, asx(1)];
        ASX_Y = [ASX_Y, asx(2)];
        ADX_U = [ADX_U, adx(1)];
        ADX_Y = [ADX_Y, adx(2)];
        PSX_U = [PSX_U, psx(1)];
        PSX_Y = [PSX_Y, psx(2)];
        PDX_U = [PDX_U, pdx(1)];
        PDX_Y = [PDX_Y, psx(2)];
        
                
        total_time = total_time + time_step;
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
        if(tempo >= 8)
            subplot(2,1,1);
            plot(timestamps, ASX_U, '', 'DisplayName', 'ASX_U'); % Primo set di dati
            hold on; % Mantiene il grafico corrente per aggiungere altri dati
            plot(timestamps, ADX_U, '', 'DisplayName', 'ADX_U'); % Secondo set di dati
            plot(timestamps, PSX_U, '', 'DisplayName', 'PSX_U'); % Terzo set di dati
            plot(timestamps, PDX_U, '', 'DisplayName', 'PDX_U'); % Quarto set di dati
            xlabel('Time (s)');
            ylabel('U (V)');
            xlim([x_min, x_max]);
            ylim([-13, 13]);
            grid on;
            hold off; % Rilascia il grafico corrente


            subplot(2,1,2);
            plot(timestamps, ASX_Y, '', 'DisplayName', 'ASX_U'); % Primo set di dati
            hold on; % Mantiene il grafico corrente per aggiungere altri dati
            plot(timestamps, ADX_Y, '', 'DisplayName', 'ADX_U'); % Secondo set di dati
            plot(timestamps, PSX_Y, '', 'DisplayName', 'PSX_U'); % Terzo set di dati
            plot(timestamps, PDX_Y, '', 'DisplayName', 'PDX_U'); % Quarto set di dati
            xlabel('Time (s)');
            ylabel('Speed (RPM)');
            xlim([x_min, x_max]);
            ylim([-180, 180]);
            grid on;
            hold off; % Rilascia il grafico corrente
            drawnow;
            tempo=0;
        end
    end
end

FS.Clear() ;
clear FS ;
clear device;
end