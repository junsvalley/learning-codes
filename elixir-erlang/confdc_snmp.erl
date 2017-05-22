-module(confdc_snmp).
-import(os, [cmd/1]).
-export([auth_key/4, priv_key/5, auth_priv_key/5, find_user/2]).

auth_key(EngineID, UserName, AuthPro, Pwd) ->
    Cmd = io_lib:format("confdc --snmpuser ~s ~s ~s ~s ~s", [EngineID, UserName, AuthPro, <<"none">>, Pwd]),
    Rst = os:cmd(Cmd),
    {_, AuthP} = re:compile("<usmUserAuthKey>(.*)</usmUserAuthKey>"),
    case re:run(Rst, AuthP) of
        {match, [{_AStart, _ALen}, {ASubStart, ASubLen}]} ->
            AuthKey = string:sub_string(Rst, ASubStart+1, ASubStart+ASubLen)
            ;
        nomatch ->
            AuthKey = <<"none">>
    end,
    %io:format("~s~n~p~n~p~n", [Cmd, Rst, AuthKey]),
    list_to_binary(AuthKey).

priv_key(EngineID, UserName, AuthPro, PiraPro, Pwd) ->
    Cmd = io_lib:format("confdc --snmpuser ~s ~s ~s ~s ~s", [EngineID, UserName, AuthPro, PiraPro, Pwd]),
    Rst = os:cmd(Cmd),
    {_, PrivP} = re:compile("<usmUserPrivKey>(.*)</usmUserPrivKey>"),
    case re:run(Rst, PrivP) of
        {match, [{_PStart, _PLen}, {PSubStart, PSubLen}]} ->
            PrivKey = string:sub_string(Rst, PSubStart+1, PSubStart+PSubLen)
            ;
        nomatch ->
            PrivKey = <<"none">>
    end,
    %io:format("~s~n~p~n~p~n", [Cmd, Rst, PrivKey]),
    KeyList = [ binary_to_integer(BX, 16) || BX <- [list_to_binary(X) || X <- string:tokens(PrivKey, ":")]],
    list_to_binary(KeyList).

auth_priv_key(EngineID, UserName, AuthPro, PiraPro, Pwd) ->
    Cmd = io_lib:format("confdc --snmpuser ~s ~s ~s ~s ~s", [EngineID, UserName, AuthPro, PiraPro, Pwd]),
    Rst = os:cmd(Cmd),
    {_, AuthP} = re:compile("<usmUserAuthKey>(.*)</usmUserAuthKey>"),
    case re:run(Rst, AuthP) of
        {match, [{_AStart, _ALen}, {ASubStart, ASubLen}]} ->
            AuthKey = string:sub_string(Rst, ASubStart+1, ASubStart+ASubLen)
            ;
        nomatch ->
            AuthKey = <<"none">>
    end,
    {_, PrivP} = re:compile("<usmUserPrivKey>(.*)</usmUserPrivKey>"),
    case re:run(Rst, PrivP) of
        {match, [{_PStart, _PLen}, {PSubStart, PSubLen}]} ->
            PrivKey = string:sub_string(Rst, PSubStart+1, PSubStart+PSubLen)
            ;
        nomatch ->
            PrivKey = <<"none">>
    end,
    io:format("~s~n~p~n~p~n~p~n", [Cmd, Rst, AuthKey, PrivKey]),
    {AuthKey, PrivKey}.

find_user(Users, UserName) ->
    MaxUsers = length(Users),
    find_user(Users, 0, MaxUsers-1, UserName).
find_user([User], MaxIdx, MaxIdx, UserName) ->
    case User of
        UserName -> MaxIdx;
        _ -> not_exists
    end;
find_user([User|Users], Idx, MaxIdx, UserName) ->
    case User of
        UserName -> Idx;
        _ -> find_user(Users, Idx+1, MaxIdx, UserName)
    end.
    
















