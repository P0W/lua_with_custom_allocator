

function lua_fun(x,y)
    registerButonClick( "callback" , x)
	registerButonClick( "callback" , 42)
    return mydoubler(x)+ mydoubler(y)
end

function lua_test( n )
    io.write( "Inside Lua test Function\n" );
	print( n );
end

function callback(widId)
   io.write( string.format("Inside Lua callback = %d\n", widId));
   
   if( widId ~= 42 ) then
   print("Jack\n");
   else
   print("Queen\n");
   end
   
end
