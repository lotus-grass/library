type
        integer = longint;

const
        dirx    : array[1 .. 4] of integer = (1, -1, 0, 0);
        diry    : array[1 .. 4] of integer = (0, 0, 1, -1);

procedure make1(nCase : integer; N, M, K : integer);
var
        p, i, j, sx, sy, step : integer;
        st      : string;
begin
        str(nCase, st);
        st := 'movement' + st + '.in';
        assign(output, st); rewrite(output);
        writeln(N, ' ', M);
        for i := 1 to M + 1 do begin
                p := k + random(5);
                if i > M then p := N;

                sx := random(10);
                sy := random(10);
                if i <= M then write(p);
                for j := 1 to p do begin
                        step := random(4) + 1;
                        sx := sx + dirx[step];
                        sy := sy + diry[step];

                        write(' ', sx, ' ', sy);
                end;
                writeln;
        end;

        close(output);
end;

procedure make2(nCase : integer; N, M, K : integer);
var
        dx, dy, p, i, j, sx, sy : integer;
        st      : string;
begin
        str(nCase, st);
        st := 'movement' + st + '.in';
        assign(output, st); rewrite(output);
        writeln(N, ' ', M);
        for i := 1 to M + 1 do begin
                p := k + random(5);
                if i > M then p := N;

                sx := random(10);
                sy := random(10);
                if i <= M then write(p);
                for j := 1 to p do begin
                        repeat
                                dx := random(5) - 2;
                                dy := random(5) - 2;
                        until (dx <> 0) or (dy <> 0);
                        sx := sx + dx;
                        sy := sy + dy;

                        write(' ', sx, ' ', sy);
                end;
                writeln;
        end;

        close(output);
end;

procedure make3(nCase : integer; N, M, K : integer);
var
        dx, dy, p, i, j, sx, sy : integer;
        st      : string;
begin
        str(nCase, st);
        st := 'movement' + st + '.in';
        assign(output, st); rewrite(output);
        writeln(N, ' ', M);
        for i := 1 to M + 1 do begin
                p := k + random(5);
                if i > M then p := N;

                sx := random(10);
                sy := random(10);
                if i <= M then write(p);
                for j := 1 to p do begin
                        if (random(1000) > 0) then begin
                                sx := sx + 1;
                                sy := sy + 1;
                        end else begin
                                sx := sx - 1000;
                                sy := sy - 1000;
                        end;

                        if (abs(sx) > 10000) or (abs(sy) > 10000) then begin
                                sx := 0;
                                sy := 0;
                        end;

                        write(' ', sx, ' ', sy);
                end;
                writeln;
        end;

        close(output);
end;

begin
	randseed := 20080312;
        make2(0, 10, 10, 2);
        make2(1, 30, 100, 2);
        make1(2, 100, 100, 2);
        make2(3, 500, 500, 2);
        make1(4, 1000, 1000, 2);
        make1(5, 10000, 3000, 2);
        make2(6, 10000, 5000, 7);
        make2(7, 10000, 3000, 10);
        make1(8, 50000, 10000, 2);
        make3(9, 100000, 50000, 30);
end.