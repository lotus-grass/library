var
	x	:longint;
	print	:boolean;

begin
	print:=false;
	while not seekeof do
	begin
		read(x);
		if print then write(' ');
		print:=true;
		write(x);
	end;
	writeln;
end.
