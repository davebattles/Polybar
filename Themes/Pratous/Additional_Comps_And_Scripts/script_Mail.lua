function Initialize()
	GetMailDetail = SELF:GetOption('GetMailDetail', 'false') == 'true' and true or false
	Maximum_Meter = tonumber(SELF:GetOption('Maximum_Meter', 5))
	page = 0
	init = true
	if GetMailDetail then
		GetMailFeed('list')
	else
		os.remove(SKIN:GetVariable('ROOTCONFIGPATH')..'DownloadFile\\gmailFeed.txt')

		local i, p = SKIN:GetVariable('Mail_Storage'):match('(%x+):(%x+)')
		if not i or p == '' or not i or p == '' then return end
		i, p =hex2str(i), hex2str(p)
		SKIN:Bang('!SetOption', 'Mail_Webparser', 'URL', 'https://'..i..':'..p..'@mail.google.com/a/gmail.com/feed/atom/')
		SKIN:Bang('!SetVariable', 'Mail_Form1', i)
		SKIN:Bang('!EnableMeasure', 'Mail_Webparser')
	end
end

function GetMailFeed(kind)
	if SKIN:GetVariable('Mail_LoggedIn') == 'false' then 
		print('Wrong Gmail address or password')
		if kind == 'list' then
			SKIN:Bang('!ShowMeterGroup', 'LogInForm')
			SKIN:Bang('!HideMeterGroup', 'MailList')
		end
		return
	else
		if kind == 'list' then SKIN:Bang('!HideMeterGroup', 'LogInForm') end
	end

	local file = io.open(SKIN:GetVariable('ROOTCONFIGPATH')..'DownloadFile\\gmailFeed.txt')
	local content = parseENT(file:read('*a'))
	file:close()
	local inboxName = content:match('<title>Gmail %- Inbox for (.-)</title>')
	

	if kind == 'module' then
		local unreadCount = content:match('<fullcount>(%d+)</fullcount>')
		SKIN:Bang('!SetOption', 'MailNotice', 'Formula', unreadCount) --For module

	elseif kind == 'list' then
		SKIN:Bang('!SetOption', 'MailList_Name', 'Text', inboxName)
		mailTable = {}
		for entry in content:gmatch('<entry>(.-)</entry>') do
			table.insert(mailTable, {})
			mailTable[#mailTable].title = entry:match('<title>(.-)</title>')
			if mailTable[#mailTable].title == '' then mailTable[#mailTable].title = 'N\A' end
			mailTable[#mailTable].summary = entry:match('<summary>(.-)</summary>')
			mailTable[#mailTable].link = 'https://mail.google.com/mail/u/'..inboxName..'/#inbox/'..entry:match('<link.-message_id=(%x+)')
			mailTable[#mailTable].sender = {entry:match('<author><name>(.-)</name><email>(.-)</email></author>')}
		end
		Max_Page = math.ceil(#mailTable / Maximum_Meter) - 1
		SetMeter(0)
	end
end


function SetMeter(dir)
	if (page+dir) <= Max_Page or (page+dir) >= 0 then
		page = page + dir
		if page + 1 > Max_Page then SKIN:Bang('!HideMeter', 'NextPage') else SKIN:Bang('!ShowMeter', 'NextPage') end
		if page - 1 < 0 then SKIN:Bang('!HideMeter', 'BackPage') else SKIN:Bang('!ShowMeter', 'BackPage') end
	else
		print('Page Not Available. Stop pressing')
		return
	end
	for i = (1 + Maximum_Meter*page), (Maximum_Meter + Maximum_Meter*page) do
		local index = i - Maximum_Meter*page
		if i <= #mailTable then
			SKIN:Bang('!ShowMeterGroup', 'Mail'..index)
			SKIN:Bang('!SetOption', 'Sender'..index, 'Text', mailTable[i].sender[1])
			SKIN:Bang('!SetOption', 'Sender'..index, 'TooltipText', mailTable[i].sender[2])
			SKIN:Bang('!SetOption', 'Title'..index, 'Text', mailTable[i].title)
			SKIN:Bang('!SetOption', 'Title'..index, 'LeftMouseUpAction', mailTable[i].link)
			SKIN:Bang('!SetOption', 'Summary'..index, 'Text', mailTable[i].summary)
			lastIndex = index
		else
			SKIN:Bang('!HideMeterGroup', 'Mail'..index)
		end
	end
	SKIN:Bang('!Update')
	if init then 
		SKIN:Bang('!SetVariable', 'LastIndex', lastIndex or 1)
		init = false
	end
end

entities = {["&amp;"] = "&",["&lt;"] = "<",["&gt;"] = ">",["&amp;"] = "&",["&quot;"] = '"',["&apos;"] = "'",["&nbsp;"]="",["<!%[CDATA%["]="",["]]>"]="",
			["<p>"]="",["</p>"]="",["<img.-/>"]="",["<div>"]="",["<div.->"]="",["</div>"]="",["<a href.-</a>"]="",["<a href.->"]="",["<a rel.->"]="",
			["</a>"]="",["</br>"]="",
			["&#(%d+)%;"] = function (x) return utf8char(tonumber(x)) end,
			["&#x(%x+)%;"] = function (x) return utf8char(tonumber(x,16)) end
			}
parseENT = 	function (s)
			for k,v in pairs(entities) do
				s = string.gsub(s,k,v)
			end return s end

--Copyright (c) 2006-2007, Kyle Smith
char = string.char
function utf8char(unicode)
	if unicode <= 0x7F then return char(unicode) end

	if (unicode <= 0x7FF) then
		local Byte0 = 0xC0 + math.floor(unicode / 0x40);
		local Byte1 = 0x80 + (unicode % 0x40);
		return char(Byte0, Byte1);
	end;

	if (unicode <= 0xFFFF) then
		local Byte0 = 0xE0 +  math.floor(unicode / 0x1000);
		local Byte1 = 0x80 + (math.floor(unicode / 0x40) % 0x40);
		local Byte2 = 0x80 + (unicode % 0x40);
		return char(Byte0, Byte1, Byte2);
	end;

	if (unicode <= 0x10FFFF) then
		local code = unicode
		local Byte3= 0x80 + (code % 0x40);
		code       = math.floor(code / 0x40)
		local Byte2= 0x80 + (code % 0x40);
		code       = math.floor(code / 0x40)
		local Byte1= 0x80 + (code % 0x40);
		code       = math.floor(code / 0x40)
		local Byte0= 0xF0 + code;

		return char(Byte0, Byte1, Byte2, Byte3);
	end;
end

function hex2str(hex)
    return (hex:gsub('..', function (h) return string.char(tonumber(string.reverse(h), 16)) end))
end

function str2hex(str)

    return (str:gsub('.', function (s) return string.reverse(string.format('%02X', string.byte(s))) end))
end

function setForm1Field()
	SKIN:Bang('!SetOption', 'Mail_Form1', 'Text', form1)
end

function setForm2Field()
	SKIN:Bang('!SetOption', 'Mail_Form2', 'Text', string.rep('*', string.len(form2)))
end

function writeAccount()
	if not form1 or form1 == '' or not form2 or form2 == '' then return end
	form1 = str2hex(form1:gsub('@','%%40'))
	form2 = str2hex(form2:gsub('@','%%40'))
	SKIN:Bang('!WriteKeyValue', 'Variables', 'Mail_Storage', form1..':'..form2, "#ROOTCONFIGPATH#\\Themes\\#Theme#\\Mail.inc")
	SKIN:Bang('!Refresh', '#ROOTCONFIG#')
	SKIN:Bang('!DeactivateConfig')
end