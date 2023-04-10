<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="supply2" urn="urn:adsk.eagle:library:372">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
Please keep in mind, that these devices are necessary for the
automatic wiring of the supply signals.&lt;p&gt;
The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="+05V" urn="urn:adsk.eagle:symbol:26987/1" library_version="2">
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.1524" layer="94"/>
<wire x1="0" y1="0.635" x2="0" y2="1.905" width="0.1524" layer="94"/>
<circle x="0" y="1.27" radius="1.27" width="0.254" layer="94"/>
<text x="-1.905" y="3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="+5V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="GND2" urn="urn:adsk.eagle:symbol:27005/1" library_version="2">
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<text x="-2.413" y="-3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND2" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="+5V" urn="urn:adsk.eagle:component:27032/1" prefix="SUPPLY" library_version="2">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="+5V" symbol="+05V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GND2" urn="urn:adsk.eagle:component:27051/1" prefix="SUPPLY" library_version="2">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="GND2" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="ArduinoMegaOutline">
<packages>
<package name="MEGAOUTLINE">
<description>Empty box</description>
<pad name="AREF" x="-26.67" y="24.13" drill="0.8"/>
<pad name="GND@1" x="-24.13" y="24.13" drill="0.8"/>
<pad name="13" x="-21.59" y="24.13" drill="0.8"/>
<pad name="12" x="-19.05" y="24.13" drill="0.8"/>
<pad name="11" x="-16.51" y="24.13" drill="0.8"/>
<pad name="10" x="-13.97" y="24.13" drill="0.8"/>
<pad name="9" x="-11.43" y="24.13" drill="0.8"/>
<pad name="8" x="-8.89" y="24.13" drill="0.8"/>
<pad name="7" x="-5.08" y="24.13" drill="0.8"/>
<pad name="6" x="-2.54" y="24.13" drill="0.8"/>
<pad name="5" x="0" y="24.13" drill="0.8"/>
<pad name="4" x="2.54" y="24.13" drill="0.8"/>
<pad name="3" x="5.08" y="24.13" drill="0.8"/>
<pad name="2" x="7.62" y="24.13" drill="0.8"/>
<pad name="1" x="10.16" y="24.13" drill="0.8"/>
<pad name="0" x="12.7" y="24.13" drill="0.8"/>
<pad name="14" x="17.78" y="24.13" drill="0.8"/>
<pad name="15" x="20.32" y="24.13" drill="0.8"/>
<pad name="16" x="22.86" y="24.13" drill="0.8"/>
<pad name="17" x="25.4" y="24.13" drill="0.8"/>
<pad name="18" x="27.94" y="24.13" drill="0.8"/>
<pad name="19" x="30.48" y="24.13" drill="0.8"/>
<pad name="20" x="33.02" y="24.13" drill="0.8"/>
<pad name="21" x="35.56" y="24.13" drill="0.8"/>
<pad name="GND@4" x="43.18" y="24.13" drill="0.8"/>
<pad name="22" x="43.18" y="21.59" drill="0.8"/>
<pad name="24" x="43.18" y="19.05" drill="0.8"/>
<pad name="26" x="43.18" y="16.51" drill="0.8"/>
<pad name="28" x="43.18" y="13.97" drill="0.8"/>
<pad name="30" x="43.18" y="11.43" drill="0.8"/>
<pad name="32" x="43.18" y="8.89" drill="0.8"/>
<pad name="34" x="43.18" y="6.35" drill="0.8"/>
<pad name="36" x="43.18" y="3.81" drill="0.8"/>
<pad name="38" x="43.18" y="1.27" drill="0.8"/>
<pad name="40" x="43.18" y="-1.27" drill="0.8"/>
<pad name="42" x="43.18" y="-3.81" drill="0.8"/>
<pad name="44" x="43.18" y="-6.35" drill="0.8"/>
<pad name="46" x="43.18" y="-8.89" drill="0.8"/>
<pad name="48" x="43.18" y="-11.43" drill="0.8"/>
<pad name="50" x="43.18" y="-13.97" drill="0.8"/>
<pad name="52" x="43.18" y="-16.51" drill="0.8"/>
<pad name="GND@6" x="43.18" y="-19.05" drill="0.8"/>
<pad name="GND@7" x="45.72" y="-19.05" drill="0.8"/>
<pad name="53" x="45.72" y="-16.51" drill="0.8"/>
<pad name="51" x="45.72" y="-13.97" drill="0.8"/>
<pad name="49" x="45.72" y="-11.43" drill="0.8"/>
<pad name="47" x="45.72" y="-8.89" drill="0.8"/>
<pad name="45" x="45.72" y="-6.35" drill="0.8"/>
<pad name="43" x="45.72" y="-3.81" drill="0.8"/>
<pad name="41" x="45.72" y="-1.27" drill="0.8"/>
<pad name="39" x="45.72" y="1.27" drill="0.8"/>
<pad name="37" x="45.72" y="3.81" drill="0.8"/>
<pad name="35" x="45.72" y="6.35" drill="0.8"/>
<pad name="33" x="45.72" y="8.89" drill="0.8"/>
<pad name="31" x="45.72" y="11.43" drill="0.8"/>
<pad name="29" x="45.72" y="13.97" drill="0.8"/>
<pad name="27" x="45.72" y="16.51" drill="0.8"/>
<pad name="25" x="45.72" y="19.05" drill="0.8"/>
<pad name="23" x="45.72" y="21.59" drill="0.8"/>
<pad name="GND@5" x="45.72" y="24.13" drill="0.8"/>
<pad name="A15" x="40.64" y="-24.13" drill="0.8"/>
<pad name="A14" x="38.1" y="-24.13" drill="0.8"/>
<pad name="A13" x="35.56" y="-24.13" drill="0.8"/>
<pad name="A12" x="33.02" y="-24.13" drill="0.8"/>
<pad name="A11" x="30.48" y="-24.13" drill="0.8"/>
<pad name="A10" x="27.94" y="-24.13" drill="0.8"/>
<pad name="A9" x="25.4" y="-24.13" drill="0.8"/>
<pad name="A8" x="22.86" y="-24.13" drill="0.8"/>
<pad name="A7" x="17.78" y="-24.13" drill="0.8"/>
<pad name="A6" x="15.24" y="-24.13" drill="0.8"/>
<pad name="A5" x="12.7" y="-24.13" drill="0.8"/>
<pad name="A4" x="10.16" y="-24.13" drill="0.8"/>
<pad name="A3" x="7.62" y="-24.13" drill="0.8"/>
<pad name="A2" x="5.08" y="-24.13" drill="0.8"/>
<pad name="A1" x="2.54" y="-24.13" drill="0.8"/>
<pad name="A0" x="0" y="-24.13" drill="0.8"/>
<pad name="VIN" x="-5.08" y="-24.13" drill="0.8"/>
<pad name="GND@3" x="-7.62" y="-24.13" drill="0.8"/>
<pad name="GND@2" x="-10.16" y="-24.13" drill="0.8"/>
<pad name="5V" x="-12.7" y="-24.13" drill="0.8"/>
<pad name="3V3" x="-15.24" y="-24.13" drill="0.8"/>
<pad name="RESET" x="-17.78" y="-24.13" drill="0.8"/>
<wire x1="-50.8" y1="26.67" x2="50.8" y2="26.67" width="0.254" layer="21"/>
<wire x1="50.8" y1="26.67" x2="50.8" y2="-26.67" width="0.254" layer="21"/>
<wire x1="50.8" y1="-26.67" x2="-50.8" y2="-26.67" width="0.254" layer="21"/>
<wire x1="-50.8" y1="-26.67" x2="-50.8" y2="26.67" width="0.254" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="MEGA_SYMBOL">
<description>Symbol as Mega card</description>
<wire x1="50.8" y1="-26.67" x2="-50.8" y2="-26.67" width="0.254" layer="94"/>
<wire x1="-50.8" y1="-26.67" x2="-50.8" y2="26.67" width="0.254" layer="94"/>
<wire x1="-50.8" y1="26.67" x2="50.8" y2="26.67" width="0.254" layer="94"/>
<wire x1="50.8" y1="26.67" x2="50.8" y2="-26.67" width="0.254" layer="94"/>
<pin name="AREF" x="-26.67" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="GND@1" x="-24.13" y="24.13" visible="pin" length="middle" rot="R90"/>
<pin name="13" x="-21.59" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="12" x="-19.05" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="11" x="-16.51" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="10" x="-13.97" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="9" x="-11.43" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="8" x="-8.89" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="7" x="-5.08" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="6" x="-2.54" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="5" x="0" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="4" x="2.54" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="3" x="5.08" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="2" x="7.62" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="1" x="10.16" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="0" x="12.7" y="24.13" visible="pad" length="middle" rot="R90"/>
<text x="10.16" y="16.51" size="1.27" layer="94" rot="R90">Tx</text>
<text x="12.7" y="16.51" size="1.27" layer="94" rot="R90">Rx</text>
<pin name="14" x="17.78" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="15" x="20.32" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="16" x="22.86" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="17" x="25.4" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="18" x="27.94" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="19" x="30.48" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="20" x="33.02" y="24.13" visible="pad" length="middle" rot="R90"/>
<pin name="21" x="35.56" y="24.13" visible="pad" length="middle" rot="R90"/>
<text x="17.78" y="15.24" size="1.27" layer="94" rot="R90">Tx3</text>
<text x="20.32" y="15.24" size="1.27" layer="94" rot="R90">Rx3</text>
<text x="22.86" y="15.24" size="1.27" layer="94" rot="R90">Tx2</text>
<text x="25.4" y="15.24" size="1.27" layer="94" rot="R90">Rx2</text>
<text x="27.94" y="15.24" size="1.27" layer="94" rot="R90">Tx1</text>
<text x="30.48" y="15.24" size="1.27" layer="94" rot="R90">Rx1</text>
<text x="33.02" y="15.24" size="1.27" layer="94" rot="R90">SDA</text>
<text x="35.56" y="15.24" size="1.27" layer="94" rot="R90">SCL</text>
<pin name="GND@4" x="43.18" y="24.13" visible="pin" length="middle" rot="R90"/>
<pin name="GND@5" x="45.72" y="24.13" visible="pin" length="middle" rot="R90"/>
<pin name="23" x="45.72" y="21.59" visible="pad" length="short"/>
<pin name="25" x="45.72" y="19.05" visible="pad" length="short"/>
<pin name="27" x="45.72" y="16.51" visible="pad" length="short"/>
<pin name="29" x="45.72" y="13.97" visible="pad" length="short"/>
<pin name="31" x="45.72" y="11.43" visible="pad" length="short"/>
<pin name="33" x="45.72" y="8.89" visible="pad" length="short"/>
<pin name="35" x="45.72" y="6.35" visible="pad" length="short"/>
<pin name="37" x="45.72" y="3.81" visible="pad" length="short"/>
<pin name="39" x="45.72" y="1.27" visible="pad" length="short"/>
<pin name="41" x="45.72" y="-1.27" visible="pad" length="short"/>
<pin name="43" x="45.72" y="-3.81" visible="pad" length="short"/>
<pin name="45" x="45.72" y="-6.35" visible="pad" length="short"/>
<pin name="47" x="45.72" y="-8.89" visible="pad" length="short"/>
<pin name="49" x="45.72" y="-11.43" visible="pad" length="short"/>
<pin name="51" x="45.72" y="-13.97" visible="pad" length="short"/>
<pin name="53" x="45.72" y="-16.51" visible="pad" length="short"/>
<pin name="GND@7" x="45.72" y="-19.05" visible="pin" length="short"/>
<pin name="22" x="43.18" y="21.59" visible="pad" length="short" rot="R180"/>
<pin name="24" x="43.18" y="19.05" visible="pad" length="short" rot="R180"/>
<pin name="26" x="43.18" y="16.51" visible="pad" length="short" rot="R180"/>
<pin name="28" x="43.18" y="13.97" visible="pad" length="short" rot="R180"/>
<pin name="30" x="43.18" y="11.43" visible="pad" length="short" rot="R180"/>
<pin name="32" x="43.18" y="8.89" visible="pad" length="short" rot="R180"/>
<pin name="34" x="43.18" y="6.35" visible="pad" length="short" rot="R180"/>
<pin name="36" x="43.18" y="3.81" visible="pad" length="short" rot="R180"/>
<pin name="38" x="43.18" y="1.27" visible="pad" length="short" rot="R180"/>
<pin name="40" x="43.18" y="-1.27" visible="pad" length="short" rot="R180"/>
<pin name="42" x="43.18" y="-3.81" visible="pad" length="short" rot="R180"/>
<pin name="44" x="43.18" y="-6.35" visible="pad" length="short" rot="R180"/>
<pin name="46" x="43.18" y="-8.89" visible="pad" length="short" rot="R180"/>
<pin name="48" x="43.18" y="-11.43" visible="pad" length="short" rot="R180"/>
<pin name="50" x="43.18" y="-13.97" visible="pad" length="short" rot="R180"/>
<pin name="52" x="43.18" y="-16.51" visible="pad" length="short" rot="R180"/>
<pin name="GND@6" x="43.18" y="-19.05" visible="pin" length="short" rot="R180"/>
<pin name="A15" x="40.64" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A14" x="38.1" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A13" x="35.56" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A12" x="33.02" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A11" x="30.48" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A10" x="27.94" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A9" x="25.4" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A8" x="22.86" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A7" x="17.78" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A6" x="15.24" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A5" x="12.7" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A4" x="10.16" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A3" x="7.62" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A2" x="5.08" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A1" x="2.54" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="A0" x="0" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="VIN" x="-5.08" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="GND@3" x="-7.62" y="-24.13" visible="pin" length="middle" rot="R270"/>
<pin name="GND@2" x="-10.16" y="-24.13" visible="pin" length="middle" rot="R270"/>
<pin name="5V" x="-12.7" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="3V3" x="-15.24" y="-24.13" visible="pad" length="middle" rot="R270"/>
<pin name="RESET" x="-17.78" y="-24.13" visible="pad" length="middle" rot="R270"/>
<text x="12.7" y="-19.05" size="1.778" layer="94" font="vector">Analog in</text>
<text x="35.56" y="-5.08" size="1.778" layer="94" font="vector" rot="R90">Digital</text>
<text x="-19.05" y="15.24" size="1.778" layer="94" font="vector">PWM and digital</text>
<wire x1="-21.59" y1="20.32" x2="-21.59" y2="17.78" width="0.254" layer="94"/>
<wire x1="-20.32" y1="16.51" x2="-21.59" y2="17.78" width="0.254" layer="94"/>
<wire x1="7.62" y1="20.32" x2="7.62" y2="17.78" width="0.254" layer="94"/>
<wire x1="7.62" y1="17.78" x2="3.81" y2="16.51" width="0.254" layer="94"/>
<text x="12.7" y="10.16" size="1.778" layer="94" font="vector">Communication</text>
<wire x1="10.16" y1="15.24" x2="10.16" y2="12.7" width="0.254" layer="94"/>
<wire x1="10.16" y1="12.7" x2="11.43" y2="11.43" width="0.254" layer="94"/>
<wire x1="35.56" y1="13.97" x2="35.56" y2="12.7" width="0.254" layer="94"/>
<wire x1="35.56" y1="12.7" x2="33.02" y2="11.43" width="0.254" layer="94"/>
<text x="-21.59" y="-1.27" size="1.778" layer="94">Arduino mega
2560</text>
<wire x1="-53.34" y1="-13.97" x2="-39.37" y2="-13.97" width="0.254" layer="94"/>
<wire x1="-39.37" y1="-13.97" x2="-39.37" y2="-22.86" width="0.254" layer="94"/>
<wire x1="-39.37" y1="-22.86" x2="-53.34" y2="-22.86" width="0.254" layer="94"/>
<wire x1="-53.34" y1="-22.86" x2="-53.34" y2="-13.97" width="0.254" layer="94"/>
<wire x1="-55.88" y1="22.86" x2="-40.64" y2="22.86" width="0.254" layer="94"/>
<wire x1="-40.64" y1="22.86" x2="-40.64" y2="10.16" width="0.254" layer="94"/>
<wire x1="-40.64" y1="10.16" x2="-55.88" y2="10.16" width="0.254" layer="94"/>
<wire x1="-55.88" y1="10.16" x2="-55.88" y2="22.86" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MEGA_DEVICE">
<description>mega card as device</description>
<gates>
<gate name="G$1" symbol="MEGA_SYMBOL" x="0" y="15.24"/>
</gates>
<devices>
<device name="" package="MEGAOUTLINE">
<connects>
<connect gate="G$1" pin="0" pad="0"/>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="16" pad="16"/>
<connect gate="G$1" pin="17" pad="17"/>
<connect gate="G$1" pin="18" pad="18"/>
<connect gate="G$1" pin="19" pad="19"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="20" pad="20"/>
<connect gate="G$1" pin="21" pad="21"/>
<connect gate="G$1" pin="22" pad="22"/>
<connect gate="G$1" pin="23" pad="23"/>
<connect gate="G$1" pin="24" pad="24"/>
<connect gate="G$1" pin="25" pad="25"/>
<connect gate="G$1" pin="26" pad="26"/>
<connect gate="G$1" pin="27" pad="27"/>
<connect gate="G$1" pin="28" pad="28"/>
<connect gate="G$1" pin="29" pad="29"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="30" pad="30"/>
<connect gate="G$1" pin="31" pad="31"/>
<connect gate="G$1" pin="32" pad="32"/>
<connect gate="G$1" pin="33" pad="33"/>
<connect gate="G$1" pin="34" pad="34"/>
<connect gate="G$1" pin="35" pad="35"/>
<connect gate="G$1" pin="36" pad="36"/>
<connect gate="G$1" pin="37" pad="37"/>
<connect gate="G$1" pin="38" pad="38"/>
<connect gate="G$1" pin="39" pad="39"/>
<connect gate="G$1" pin="3V3" pad="3V3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="40" pad="40"/>
<connect gate="G$1" pin="41" pad="41"/>
<connect gate="G$1" pin="42" pad="42"/>
<connect gate="G$1" pin="43" pad="43"/>
<connect gate="G$1" pin="44" pad="44"/>
<connect gate="G$1" pin="45" pad="45"/>
<connect gate="G$1" pin="46" pad="46"/>
<connect gate="G$1" pin="47" pad="47"/>
<connect gate="G$1" pin="48" pad="48"/>
<connect gate="G$1" pin="49" pad="49"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="50" pad="50"/>
<connect gate="G$1" pin="51" pad="51"/>
<connect gate="G$1" pin="52" pad="52"/>
<connect gate="G$1" pin="53" pad="53"/>
<connect gate="G$1" pin="5V" pad="5V"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
<connect gate="G$1" pin="A0" pad="A0"/>
<connect gate="G$1" pin="A1" pad="A1"/>
<connect gate="G$1" pin="A10" pad="A10"/>
<connect gate="G$1" pin="A11" pad="A11"/>
<connect gate="G$1" pin="A12" pad="A12"/>
<connect gate="G$1" pin="A13" pad="A13"/>
<connect gate="G$1" pin="A14" pad="A14"/>
<connect gate="G$1" pin="A15" pad="A15"/>
<connect gate="G$1" pin="A2" pad="A2"/>
<connect gate="G$1" pin="A3" pad="A3"/>
<connect gate="G$1" pin="A4" pad="A4"/>
<connect gate="G$1" pin="A5" pad="A5"/>
<connect gate="G$1" pin="A6" pad="A6"/>
<connect gate="G$1" pin="A7" pad="A7"/>
<connect gate="G$1" pin="A8" pad="A8"/>
<connect gate="G$1" pin="A9" pad="A9"/>
<connect gate="G$1" pin="AREF" pad="AREF"/>
<connect gate="G$1" pin="GND@1" pad="GND@1"/>
<connect gate="G$1" pin="GND@2" pad="GND@2"/>
<connect gate="G$1" pin="GND@3" pad="GND@3"/>
<connect gate="G$1" pin="GND@4" pad="GND@4"/>
<connect gate="G$1" pin="GND@5" pad="GND@5"/>
<connect gate="G$1" pin="GND@6" pad="GND@6"/>
<connect gate="G$1" pin="GND@7" pad="GND@7"/>
<connect gate="G$1" pin="RESET" pad="RESET"/>
<connect gate="G$1" pin="VIN" pad="VIN"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-panduit" urn="urn:adsk.eagle:library:169">
<description>&lt;b&gt;Panduit Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="057-010-0" urn="urn:adsk.eagle:footprint:9178/1" library_version="2">
<description>&lt;b&gt;CONNECTOR&lt;/b&gt;&lt;p&gt;
series 057 contact pc board low profile headers&lt;p&gt;
angled</description>
<wire x1="-1.9" y1="-0.23" x2="-1.9" y2="5.86" width="0.2032" layer="21"/>
<wire x1="-1.9" y1="-0.23" x2="1.9" y2="-0.23" width="0.2032" layer="21"/>
<wire x1="1.9" y1="-0.23" x2="1.9" y2="5.86" width="0.2032" layer="21"/>
<wire x1="-5.8" y1="5.22" x2="-5.1" y2="3.25" width="0.4064" layer="21"/>
<wire x1="-5.1" y1="3.25" x2="-4.4" y2="5.22" width="0.4064" layer="21"/>
<wire x1="-4.4" y1="5.22" x2="-5.8" y2="5.22" width="0.4064" layer="21"/>
<wire x1="-10.21" y1="-2.54" x2="-10.21" y2="5.86" width="0.2032" layer="21"/>
<wire x1="10.21" y1="5.86" x2="10.21" y2="-2.44" width="0.2032" layer="21"/>
<wire x1="-10.16" y1="-2.54" x2="-7.62" y2="-2.54" width="0.2032" layer="21"/>
<wire x1="-7.62" y1="-2.54" x2="-7.62" y2="-5.98" width="0.2032" layer="21"/>
<wire x1="10.16" y1="-2.54" x2="7.62" y2="-2.54" width="0.2032" layer="21"/>
<wire x1="7.62" y1="-2.54" x2="7.62" y2="-6.05" width="0.2032" layer="21"/>
<wire x1="7.61" y1="-6.04" x2="-7.61" y2="-6.04" width="0.2032" layer="21"/>
<wire x1="-10.21" y1="5.86" x2="10.21" y2="5.86" width="0.2032" layer="21"/>
<pad name="1" x="-5.08" y="-5.08" drill="1" shape="octagon"/>
<pad name="2" x="-5.08" y="-2.54" drill="1" shape="octagon"/>
<pad name="3" x="-2.54" y="-5.08" drill="1" shape="octagon"/>
<pad name="4" x="-2.54" y="-2.54" drill="1" shape="octagon"/>
<pad name="5" x="0" y="-5.08" drill="1" shape="octagon"/>
<pad name="6" x="0" y="-2.54" drill="1" shape="octagon"/>
<pad name="7" x="2.54" y="-5.08" drill="1" shape="octagon"/>
<pad name="8" x="2.54" y="-2.54" drill="1" shape="octagon"/>
<pad name="9" x="5.08" y="-5.08" drill="1" shape="octagon"/>
<pad name="10" x="5.08" y="-2.54" drill="1" shape="octagon"/>
<text x="-6.35" y="-8.89" size="1.778" layer="25">&gt;NAME</text>
<text x="-8.89" y="6.35" size="1.778" layer="27">&gt;VALUE</text>
<hole x="-13.48" y="3.66" drill="2.8"/>
<hole x="13.73" y="3.66" drill="2.8"/>
</package>
<package name="057-010-1" urn="urn:adsk.eagle:footprint:9179/1" library_version="2">
<description>&lt;b&gt;CONNECTOR&lt;/b&gt;&lt;p&gt;
series 057 contact pc board low profile headers&lt;p&gt;
straight</description>
<wire x1="-1.9" y1="-3.32" x2="-1.9" y2="-4.03" width="0.2032" layer="21"/>
<wire x1="1.9" y1="-3.32" x2="1.9" y2="-4.03" width="0.2032" layer="21"/>
<wire x1="-7.5" y1="-1.97" x2="-6.8" y2="-3.04" width="0.4064" layer="21"/>
<wire x1="-6.8" y1="-3.04" x2="-6.1" y2="-1.97" width="0.4064" layer="21"/>
<wire x1="-6.1" y1="-1.97" x2="-7.5" y2="-1.97" width="0.4064" layer="21"/>
<wire x1="-10.21" y1="-4.1" x2="-10.21" y2="4.1" width="0.2032" layer="21"/>
<wire x1="-10.21" y1="-4.1" x2="10.21" y2="-4.1" width="0.2032" layer="21"/>
<wire x1="10.21" y1="-4.1" x2="10.21" y2="4.1" width="0.2032" layer="21"/>
<wire x1="10.21" y1="4.1" x2="-10.21" y2="4.1" width="0.2032" layer="21"/>
<wire x1="-9.41" y1="-3.3" x2="-9.41" y2="3.3" width="0.2032" layer="21"/>
<wire x1="-9.41" y1="3.3" x2="9.41" y2="3.3" width="0.2032" layer="21"/>
<wire x1="9.41" y1="3.3" x2="9.41" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="9.41" y1="-3.3" x2="1.9" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="-1.9" y1="-3.3" x2="-9.41" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="-10.21" y1="4.1" x2="-9.41" y2="3.3" width="0.2032" layer="21"/>
<wire x1="-10.21" y1="-4.1" x2="-9.41" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="10.21" y1="4.1" x2="9.41" y2="3.3" width="0.2032" layer="21"/>
<wire x1="9.41" y1="-3.3" x2="10.21" y2="-4.1" width="0.2032" layer="21"/>
<pad name="1" x="-5.08" y="-1.27" drill="1" shape="octagon"/>
<pad name="2" x="-5.08" y="1.27" drill="1" shape="octagon"/>
<pad name="3" x="-2.54" y="-1.27" drill="1" shape="octagon"/>
<pad name="4" x="-2.54" y="1.27" drill="1" shape="octagon"/>
<pad name="5" x="0" y="-1.27" drill="1" shape="octagon"/>
<pad name="6" x="0" y="1.27" drill="1" shape="octagon"/>
<pad name="7" x="2.54" y="-1.27" drill="1" shape="octagon"/>
<pad name="8" x="2.54" y="1.27" drill="1" shape="octagon"/>
<pad name="9" x="5.08" y="-1.27" drill="1" shape="octagon"/>
<pad name="10" x="5.08" y="1.27" drill="1" shape="octagon"/>
<text x="-6.33" y="-6.88" size="1.778" layer="25">&gt;NAME</text>
<text x="-8.35" y="4.55" size="1.778" layer="27">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="057-010-0" urn="urn:adsk.eagle:package:9200/1" type="box" library_version="2">
<description>CONNECTOR
series 057 contact pc board low profile headers
angled</description>
<packageinstances>
<packageinstance name="057-010-0"/>
</packageinstances>
</package3d>
<package3d name="057-010-1" urn="urn:adsk.eagle:package:9203/1" type="box" library_version="2">
<description>CONNECTOR
series 057 contact pc board low profile headers
straight</description>
<packageinstances>
<packageinstance name="057-010-1"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="MV" urn="urn:adsk.eagle:symbol:9158/1" library_version="2">
<wire x1="0" y1="0" x2="-1.27" y2="0" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.27" y2="0" width="0.1524" layer="94"/>
<text x="1.016" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<text x="-2.54" y="1.905" size="1.778" layer="96">&gt;VALUE</text>
<pin name="S" x="-5.08" y="0" visible="off" length="short" direction="pas"/>
</symbol>
<symbol name="M" urn="urn:adsk.eagle:symbol:9159/1" library_version="2">
<wire x1="0" y1="0" x2="-1.27" y2="0" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.27" y2="0" width="0.1524" layer="94"/>
<text x="1.016" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<pin name="S" x="-5.08" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="057-010-" urn="urn:adsk.eagle:component:9212/2" prefix="X" library_version="2">
<description>&lt;b&gt;CONNECTOR&lt;/b&gt;&lt;p&gt;
10-pin series 057 contact pc board low profile headers</description>
<gates>
<gate name="-1" symbol="MV" x="-10.16" y="43.18" addlevel="always" swaplevel="1"/>
<gate name="-2" symbol="M" x="12.7" y="43.18" addlevel="always" swaplevel="1"/>
<gate name="-3" symbol="M" x="-10.16" y="38.1" addlevel="always" swaplevel="1"/>
<gate name="-4" symbol="M" x="12.7" y="38.1" addlevel="always" swaplevel="1"/>
<gate name="-5" symbol="M" x="-10.16" y="33.02" addlevel="always" swaplevel="1"/>
<gate name="-6" symbol="M" x="12.7" y="33.02" addlevel="always" swaplevel="1"/>
<gate name="-7" symbol="M" x="-10.16" y="27.94" addlevel="always" swaplevel="1"/>
<gate name="-8" symbol="M" x="12.7" y="27.94" addlevel="always" swaplevel="1"/>
<gate name="-9" symbol="M" x="-10.16" y="22.86" addlevel="always" swaplevel="1"/>
<gate name="-10" symbol="M" x="12.7" y="22.86" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="0" package="057-010-0">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-10" pin="S" pad="10"/>
<connect gate="-2" pin="S" pad="2"/>
<connect gate="-3" pin="S" pad="3"/>
<connect gate="-4" pin="S" pad="4"/>
<connect gate="-5" pin="S" pad="5"/>
<connect gate="-6" pin="S" pad="6"/>
<connect gate="-7" pin="S" pad="7"/>
<connect gate="-8" pin="S" pad="8"/>
<connect gate="-9" pin="S" pad="9"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:9200/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
<attribute name="POPULARITY" value="0" constant="no"/>
</technology>
</technologies>
</device>
<device name="1" package="057-010-1">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-10" pin="S" pad="10"/>
<connect gate="-2" pin="S" pad="2"/>
<connect gate="-3" pin="S" pad="3"/>
<connect gate="-4" pin="S" pad="4"/>
<connect gate="-5" pin="S" pad="5"/>
<connect gate="-6" pin="S" pad="6"/>
<connect gate="-7" pin="S" pad="7"/>
<connect gate="-8" pin="S" pad="8"/>
<connect gate="-9" pin="S" pad="9"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:9203/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
<attribute name="POPULARITY" value="6" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="switch-misc" urn="urn:adsk.eagle:library:376">
<description>&lt;b&gt;Switches&lt;/b&gt;&lt;p&gt;
Marquardt, RAFI, ITT, and others&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="DT6" urn="urn:adsk.eagle:footprint:27398/1" library_version="3">
<description>&lt;b&gt;ITT SWITCH&lt;/b&gt;</description>
<wire x1="1.016" y1="4.826" x2="1.016" y2="5.588" width="0.1524" layer="21"/>
<wire x1="1.016" y1="4.826" x2="-1.016" y2="4.826" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="4.826" x2="-1.016" y2="5.588" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-5.969" x2="1.016" y2="-5.588" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="-5.969" x2="-1.016" y2="-5.588" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-4.826" x2="-1.016" y2="-4.826" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="-5.588" x2="1.016" y2="-5.588" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="-5.588" x2="-1.016" y2="-4.826" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-5.588" x2="1.016" y2="-4.826" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="5.588" x2="1.016" y2="5.588" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="5.588" x2="-1.016" y2="5.969" width="0.1524" layer="21"/>
<wire x1="1.016" y1="5.588" x2="1.016" y2="5.969" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="2.54" x2="1.143" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.143" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.159" y1="0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-2.54" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="0" x2="-1.905" y2="0" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="-2.54" x2="1.143" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="0" x2="-0.508" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.127" y1="0" x2="0.889" y2="0" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.143" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="2.54" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="2.921" y1="0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0" x2="2.286" y2="0" width="0.1524" layer="21"/>
<wire x1="-5.334" y1="-2.9512" x2="-5.334" y2="2.9512" width="0.1524" layer="21" curve="302.09017"/>
<wire x1="-2.347" y1="3.9236" x2="2.347" y2="3.9236" width="0.1524" layer="21" curve="-61.77363"/>
<wire x1="-1.8556" y1="3.7578" x2="1.8556" y2="3.7578" width="0.1524" layer="21" curve="-52.56028"/>
<wire x1="-1.8556" y1="-3.7578" x2="1.8556" y2="-3.7578" width="0.1524" layer="21" curve="52.56028"/>
<wire x1="-2.347" y1="-3.9236" x2="2.347" y2="-3.9236" width="0.1524" layer="21" curve="61.77363"/>
<wire x1="-5.334" y1="-2.9512" x2="-5.334" y2="2.9512" width="0.1524" layer="21"/>
<wire x1="-3.7578" y1="1.8556" x2="-3.7578" y2="-1.8556" width="0.1524" layer="21" curve="52.56028"/>
<wire x1="-3.9236" y1="2.347" x2="-3.9236" y2="-2.347" width="0.1524" layer="21" curve="61.77363"/>
<wire x1="-3.7578" y1="-1.8556" x2="-1.8556" y2="-3.7578" width="0.1524" layer="51" curve="37.43972"/>
<wire x1="-3.9236" y1="-2.347" x2="-2.347" y2="-3.9236" width="0.1524" layer="51" curve="28.22637"/>
<wire x1="-3.9236" y1="2.347" x2="-2.347" y2="3.9236" width="0.1524" layer="51" curve="-28.22637"/>
<wire x1="-3.7578" y1="1.8556" x2="-1.8556" y2="3.7578" width="0.1524" layer="51" curve="-37.43972"/>
<wire x1="3.7578" y1="-1.8556" x2="3.7578" y2="1.8556" width="0.1524" layer="21" curve="52.56028"/>
<wire x1="3.9236" y1="-2.347" x2="3.9236" y2="2.347" width="0.1524" layer="21" curve="61.77363"/>
<wire x1="1.8556" y1="-3.7578" x2="3.7578" y2="-1.8556" width="0.1524" layer="51" curve="37.43972"/>
<wire x1="2.347" y1="-3.9236" x2="3.9236" y2="-2.347" width="0.1524" layer="51" curve="28.22637"/>
<wire x1="1.8556" y1="3.7578" x2="3.7578" y2="1.8556" width="0.1524" layer="51" curve="-37.43972"/>
<wire x1="2.347" y1="3.9236" x2="3.9236" y2="2.347" width="0.1524" layer="51" curve="-28.22637"/>
<pad name="1" x="-2.54" y="2.54" drill="1.1176" shape="octagon"/>
<pad name="2" x="2.54" y="2.54" drill="1.1176" shape="octagon"/>
<pad name="3" x="2.54" y="-2.54" drill="1.1176" shape="octagon"/>
<pad name="4" x="-2.54" y="-2.54" drill="1.1176" shape="octagon"/>
<text x="-2.54" y="6.477" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-7.874" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="DTE6" urn="urn:adsk.eagle:footprint:27399/1" library_version="3">
<description>&lt;b&gt;ITT SWITCH&lt;/b&gt;</description>
<wire x1="1.016" y1="4.826" x2="1.016" y2="5.588" width="0.1524" layer="21"/>
<wire x1="1.016" y1="4.826" x2="-1.016" y2="4.826" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="4.826" x2="-1.016" y2="5.588" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-5.969" x2="1.016" y2="-5.588" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="-5.969" x2="-1.016" y2="-5.588" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-4.826" x2="-1.016" y2="-4.826" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="-5.588" x2="1.016" y2="-5.588" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="-5.588" x2="-1.016" y2="-4.826" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-5.588" x2="1.016" y2="-4.826" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="5.588" x2="1.016" y2="5.588" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="5.588" x2="-1.016" y2="5.969" width="0.1524" layer="21"/>
<wire x1="1.016" y1="5.588" x2="1.016" y2="5.969" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="2.54" x2="1.27" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.159" y1="0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-2.54" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="0" x2="-1.905" y2="0" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-2.54" x2="1.27" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="0" x2="-0.508" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.127" y1="0" x2="0.889" y2="0" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="2.54" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.921" y1="0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0" x2="2.286" y2="0" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-3.429" x2="-3.81" y2="3.429" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-3.429" x2="-3.429" y2="-3.81" width="0.1524" layer="21"/>
<wire x1="3.81" y1="-3.429" x2="3.429" y2="-3.81" width="0.1524" layer="21"/>
<wire x1="3.429" y1="-3.81" x2="-3.429" y2="-3.81" width="0.1524" layer="21"/>
<wire x1="3.429" y1="3.81" x2="3.81" y2="3.429" width="0.1524" layer="21"/>
<wire x1="3.81" y1="3.429" x2="3.81" y2="-3.429" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="3.429" x2="-3.429" y2="3.81" width="0.1524" layer="21"/>
<wire x1="-3.429" y1="3.81" x2="3.429" y2="3.81" width="0.1524" layer="21"/>
<wire x1="-5.334" y1="-2.9512" x2="-5.334" y2="2.9512" width="0.1524" layer="21" curve="302.09017"/>
<wire x1="-5.334" y1="-2.9512" x2="-5.334" y2="2.9512" width="0.1524" layer="21"/>
<pad name="1" x="-2.54" y="2.54" drill="1.1176" shape="octagon"/>
<pad name="2" x="2.54" y="2.54" drill="1.1176" shape="octagon"/>
<pad name="3" x="2.54" y="-2.54" drill="1.1176" shape="octagon"/>
<pad name="4" x="-2.54" y="-2.54" drill="1.1176" shape="octagon"/>
<text x="-2.54" y="6.477" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-7.747" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="DTE6K" urn="urn:adsk.eagle:footprint:27400/1" library_version="3">
<description>&lt;b&gt;ITT SWITCH&lt;/b&gt;</description>
<wire x1="-1.27" y1="2.54" x2="1.27" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.159" y1="0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-2.54" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="0" x2="-1.905" y2="0" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-2.54" x2="1.27" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="0" x2="-0.508" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.127" y1="0" x2="0.889" y2="0" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="2.54" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.921" y1="0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0" x2="2.286" y2="0" width="0.1524" layer="21"/>
<wire x1="-6.223" y1="-5.207" x2="-6.223" y2="5.207" width="0.1524" layer="21"/>
<wire x1="5.207" y1="-6.223" x2="-5.207" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="6.223" y1="5.207" x2="6.223" y2="-5.207" width="0.1524" layer="21"/>
<wire x1="-5.207" y1="6.223" x2="5.207" y2="6.223" width="0.1524" layer="21"/>
<wire x1="5.207" y1="-6.223" x2="6.223" y2="-5.207" width="0.1524" layer="21" curve="90"/>
<wire x1="-6.223" y1="-5.207" x2="-5.207" y2="-6.223" width="0.1524" layer="21" curve="90"/>
<wire x1="5.207" y1="6.223" x2="6.223" y2="5.207" width="0.1524" layer="21" curve="-90"/>
<wire x1="-6.223" y1="5.207" x2="-5.207" y2="6.223" width="0.1524" layer="21" curve="-90"/>
<wire x1="5.715" y1="5.207" x2="5.715" y2="-5.207" width="0.1524" layer="21"/>
<wire x1="-5.207" y1="5.715" x2="5.207" y2="5.715" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-5.207" x2="-5.715" y2="5.207" width="0.1524" layer="21"/>
<wire x1="5.207" y1="-5.715" x2="-5.207" y2="-5.715" width="0.1524" layer="21"/>
<wire x1="5.207" y1="-5.715" x2="5.715" y2="-5.207" width="0.1524" layer="21" curve="90"/>
<wire x1="-5.715" y1="-5.207" x2="-5.207" y2="-5.715" width="0.1524" layer="21" curve="90"/>
<wire x1="-5.715" y1="5.207" x2="-5.207" y2="5.715" width="0.1524" layer="21" curve="-90"/>
<wire x1="5.207" y1="5.715" x2="5.715" y2="5.207" width="0.1524" layer="21" curve="-90"/>
<pad name="1" x="-2.54" y="2.54" drill="1.1176" shape="octagon"/>
<pad name="2" x="2.54" y="2.54" drill="1.1176" shape="octagon"/>
<pad name="3" x="2.54" y="-2.54" drill="1.1176" shape="octagon"/>
<pad name="4" x="-2.54" y="-2.54" drill="1.1176" shape="octagon"/>
<text x="-5.08" y="6.604" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.81" y="-5.207" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="DT6" urn="urn:adsk.eagle:package:27430/1" type="box" library_version="3">
<description>ITT SWITCH</description>
<packageinstances>
<packageinstance name="DT6"/>
</packageinstances>
</package3d>
<package3d name="DTE6" urn="urn:adsk.eagle:package:27432/1" type="box" library_version="3">
<description>ITT SWITCH</description>
<packageinstances>
<packageinstance name="DTE6"/>
</packageinstances>
</package3d>
<package3d name="DTE6K" urn="urn:adsk.eagle:package:27433/1" type="box" library_version="3">
<description>ITT SWITCH</description>
<packageinstances>
<packageinstance name="DTE6K"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="TS2" urn="urn:adsk.eagle:symbol:27397/1" library_version="3">
<wire x1="0" y1="2.032" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="-6.35" y1="1.905" x2="-5.08" y2="1.905" width="0.254" layer="94"/>
<wire x1="-6.35" y1="1.905" x2="-6.35" y2="0" width="0.254" layer="94"/>
<wire x1="-6.35" y1="-1.905" x2="-5.08" y2="-1.905" width="0.254" layer="94"/>
<wire x1="-6.35" y1="0" x2="-4.445" y2="0" width="0.1524" layer="94"/>
<wire x1="-6.35" y1="0" x2="-6.35" y2="-1.905" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.905" y2="0" width="0.1524" layer="94"/>
<wire x1="-1.27" y1="0" x2="-0.635" y2="0" width="0.1524" layer="94"/>
<wire x1="-3.81" y1="0" x2="-3.175" y2="0" width="0.1524" layer="94"/>
<wire x1="2.54" y1="2.54" x2="0" y2="2.54" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-2.54" x2="-1.016" y2="2.032" width="0.254" layer="94"/>
<circle x="0" y="-2.54" radius="0.127" width="0.4064" layer="94"/>
<circle x="0" y="2.54" radius="0.127" width="0.4064" layer="94"/>
<text x="-6.985" y="-1.905" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<text x="-4.445" y="2.54" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="S" x="0" y="5.08" visible="pad" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="P" x="0" y="-5.08" visible="pad" length="short" direction="pas" swaplevel="2" rot="R90"/>
<pin name="P@1" x="2.54" y="-5.08" visible="pad" length="short" direction="pas" swaplevel="2" rot="R90"/>
<pin name="S@1" x="2.54" y="5.08" visible="pad" length="short" direction="pas" swaplevel="1" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="DT" urn="urn:adsk.eagle:component:27457/2" prefix="S" library_version="3">
<description>&lt;b&gt;ITT SWITCH&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="TS2" x="0" y="0"/>
</gates>
<devices>
<device name="6" package="DT6">
<connects>
<connect gate="1" pin="P" pad="3"/>
<connect gate="1" pin="P@1" pad="4"/>
<connect gate="1" pin="S" pad="1"/>
<connect gate="1" pin="S@1" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:27430/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="POPULARITY" value="0" constant="no"/>
</technology>
</technologies>
</device>
<device name="E6" package="DTE6">
<connects>
<connect gate="1" pin="P" pad="3"/>
<connect gate="1" pin="P@1" pad="4"/>
<connect gate="1" pin="S" pad="1"/>
<connect gate="1" pin="S@1" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:27432/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="POPULARITY" value="0" constant="no"/>
</technology>
</technologies>
</device>
<device name="E6K" package="DTE6K">
<connects>
<connect gate="1" pin="P" pad="3"/>
<connect gate="1" pin="P@1" pad="4"/>
<connect gate="1" pin="S" pad="1"/>
<connect gate="1" pin="S@1" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:27433/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="POPULARITY" value="0" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="ngspice-simulation" urn="urn:adsk.eagle:library:527439">
<description>SPICE compatible library parts</description>
<packages>
</packages>
<symbols>
<symbol name="R" urn="urn:adsk.eagle:symbol:527454/4" library_version="18">
<description>RESISTOR</description>
<wire x1="-2.54" y1="-0.889" x2="2.54" y2="-0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.889" x2="2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<text x="-2.54" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-6.35" size="1.778" layer="97">&gt;SPICEMODEL</text>
<text x="-2.54" y="-3.81" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.54" y="-8.89" size="1.778" layer="97">&gt;SPICEEXTRA</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="R" urn="urn:adsk.eagle:component:527474/6" prefix="R" uservalue="yes" library_version="18">
<description>RESISTOR</description>
<gates>
<gate name="G$1" symbol="R" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name="">
<attribute name="_EXTERNAL_" value="" constant="no"/>
</technology>
</technologies>
</device>
</devices>
<spice>
<pinmapping spiceprefix="R">
<pinmap gate="G$1" pin="1" pinorder="1"/>
<pinmap gate="G$1" pin="2" pinorder="2"/>
</pinmapping>
</spice>
</deviceset>
</devicesets>
</library>
<library name="led" urn="urn:adsk.eagle:library:259">
<description>&lt;b&gt;LEDs&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;&lt;br&gt;
Extended by Federico Battaglin &lt;author&gt;&amp;lt;federico.rd@fdpinternational.com&amp;gt;&lt;/author&gt; with DUOLED</description>
<packages>
<package name="LED3MM" urn="urn:adsk.eagle:footprint:15654/1" library_version="5">
<description>&lt;B&gt;LED&lt;/B&gt;&lt;p&gt;
3 mm, round</description>
<wire x1="1.5748" y1="-1.27" x2="1.5748" y2="1.27" width="0.254" layer="51"/>
<wire x1="-1.524" y1="0" x2="-1.1708" y2="0.9756" width="0.1524" layer="51" curve="-39.80361"/>
<wire x1="-1.524" y1="0" x2="-1.1391" y2="-1.0125" width="0.1524" layer="51" curve="41.633208"/>
<wire x1="1.1571" y1="0.9918" x2="1.524" y2="0" width="0.1524" layer="51" curve="-40.601165"/>
<wire x1="1.1708" y1="-0.9756" x2="1.524" y2="0" width="0.1524" layer="51" curve="39.80361"/>
<wire x1="0" y1="1.524" x2="1.2401" y2="0.8858" width="0.1524" layer="21" curve="-54.461337"/>
<wire x1="-1.2192" y1="0.9144" x2="0" y2="1.524" width="0.1524" layer="21" curve="-53.130102"/>
<wire x1="0" y1="-1.524" x2="1.203" y2="-0.9356" width="0.1524" layer="21" curve="52.126876"/>
<wire x1="-1.203" y1="-0.9356" x2="0" y2="-1.524" width="0.1524" layer="21" curve="52.126876"/>
<wire x1="-0.635" y1="0" x2="0" y2="0.635" width="0.1524" layer="51" curve="-90"/>
<wire x1="-1.016" y1="0" x2="0" y2="1.016" width="0.1524" layer="51" curve="-90"/>
<wire x1="0" y1="-0.635" x2="0.635" y2="0" width="0.1524" layer="51" curve="90"/>
<wire x1="0" y1="-1.016" x2="1.016" y2="0" width="0.1524" layer="51" curve="90"/>
<wire x1="0" y1="2.032" x2="1.561" y2="1.3009" width="0.254" layer="21" curve="-50.193108"/>
<wire x1="-1.7929" y1="0.9562" x2="0" y2="2.032" width="0.254" layer="21" curve="-61.926949"/>
<wire x1="0" y1="-2.032" x2="1.5512" y2="-1.3126" width="0.254" layer="21" curve="49.763022"/>
<wire x1="-1.7643" y1="-1.0082" x2="0" y2="-2.032" width="0.254" layer="21" curve="60.255215"/>
<wire x1="-2.032" y1="0" x2="-1.7891" y2="0.9634" width="0.254" layer="51" curve="-28.301701"/>
<wire x1="-2.032" y1="0" x2="-1.7306" y2="-1.065" width="0.254" layer="51" curve="31.60822"/>
<pad name="A" x="-1.27" y="0" drill="0.8128" shape="octagon"/>
<pad name="K" x="1.27" y="0" drill="0.8128" shape="octagon"/>
<text x="1.905" y="0.381" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="1.905" y="-1.651" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="LED3MM" urn="urn:adsk.eagle:package:15797/1" type="box" library_version="5">
<description>LED
3 mm, round</description>
<packageinstances>
<packageinstance name="LED3MM"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="LED" urn="urn:adsk.eagle:symbol:15639/2" library_version="5">
<wire x1="1.27" y1="0" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="-2.54" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-2.032" y1="-0.762" x2="-3.429" y2="-2.159" width="0.1524" layer="94"/>
<wire x1="-1.905" y1="-1.905" x2="-3.302" y2="-3.302" width="0.1524" layer="94"/>
<text x="3.556" y="-4.572" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<text x="5.715" y="-4.572" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="C" x="0" y="-5.08" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="A" x="0" y="2.54" visible="off" length="short" direction="pas" rot="R270"/>
<polygon width="0.1524" layer="94">
<vertex x="-3.429" y="-2.159"/>
<vertex x="-3.048" y="-1.27"/>
<vertex x="-2.54" y="-1.778"/>
</polygon>
<polygon width="0.1524" layer="94">
<vertex x="-3.302" y="-3.302"/>
<vertex x="-2.921" y="-2.413"/>
<vertex x="-2.413" y="-2.921"/>
</polygon>
</symbol>
</symbols>
<devicesets>
<deviceset name="TLLG4400" urn="urn:adsk.eagle:component:15909/3" prefix="LED" library_version="5">
<description>&lt;b&gt;Low Current (2mA) LED 3 mm Tinted Diffused Package&lt;/b&gt; color &lt;b&gt;&lt;font color="green"&gt;GREEN&lt;/font&gt;&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="http://www.farnell.com/datasheets/391098.pdf"&gt; Data sheet&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="LED" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LED3MM">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="K"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:15797/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="MF" value="VISHAY SEMICONDUCTOR" constant="no"/>
<attribute name="OC_FARNELL" value="1612435" constant="no"/>
<attribute name="POPULARITY" value="7" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-hirschmann" urn="urn:adsk.eagle:library:153">
<description>&lt;b&gt;Hirschmann Connectors&lt;/b&gt;&lt;p&gt;
Audio, scart, microphone, headphone&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="SPB5" urn="urn:adsk.eagle:footprint:7429/1" library_version="2">
<description>&lt;B&gt;CONNECTOR&lt;/B&gt;&lt;p&gt;
5 pins</description>
<wire x1="-5.588" y1="2.032" x2="5.588" y2="2.032" width="0.1524" layer="21"/>
<wire x1="5.588" y1="-2.032" x2="-5.588" y2="-2.032" width="0.1524" layer="21"/>
<wire x1="5.207" y1="1.397" x2="5.588" y2="1.016" width="0.1524" layer="21" curve="-90"/>
<wire x1="-5.588" y1="-1.016" x2="-5.207" y2="-1.397" width="0.1524" layer="21" curve="90"/>
<wire x1="5.207" y1="-1.397" x2="5.588" y2="-1.016" width="0.1524" layer="21" curve="90"/>
<wire x1="5.588" y1="-2.032" x2="5.588" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-5.207" y1="-1.397" x2="5.207" y2="-1.397" width="0.1524" layer="21"/>
<wire x1="-5.588" y1="2.032" x2="-5.588" y2="0.508" width="0.1524" layer="21"/>
<wire x1="-5.588" y1="0.508" x2="-5.588" y2="-2.032" width="0.1524" layer="21"/>
<wire x1="-5.588" y1="0.508" x2="-4.699" y2="1.397" width="0.1524" layer="21"/>
<wire x1="-4.699" y1="1.397" x2="5.207" y2="1.397" width="0.1524" layer="21"/>
<circle x="0" y="0" radius="0.508" width="0.1524" layer="51"/>
<circle x="2.032" y="0" radius="0.508" width="0.1524" layer="51"/>
<circle x="-2.032" y="0" radius="0.508" width="0.1524" layer="51"/>
<circle x="-4.064" y="0" radius="0.508" width="0.1524" layer="51"/>
<circle x="4.064" y="0" radius="0.508" width="0.1524" layer="51"/>
<pad name="1" x="-4.064" y="0" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-2.032" y="0" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="0" y="0" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="2.032" y="0" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="4.064" y="0" drill="0.8128" shape="long" rot="R90"/>
<text x="-5.588" y="2.286" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.588" y="-3.556" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
</packages>
<packages3d>
<package3d name="SPB5" urn="urn:adsk.eagle:package:7457/1" type="box" library_version="2">
<description>CONNECTOR
5 pins</description>
<packageinstances>
<packageinstance name="SPB5"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="B5P" urn="urn:adsk.eagle:symbol:7428/1" library_version="2">
<wire x1="0" y1="5.715" x2="0.635" y2="5.08" width="0.254" layer="94" curve="-90" cap="flat"/>
<wire x1="0.635" y1="5.08" x2="0" y2="4.445" width="0.254" layer="94" curve="-90" cap="flat"/>
<wire x1="0" y1="0.635" x2="0.635" y2="0" width="0.254" layer="94" curve="-90" cap="flat"/>
<wire x1="0.635" y1="0" x2="0" y2="-0.635" width="0.254" layer="94" curve="-90" cap="flat"/>
<wire x1="0" y1="3.175" x2="0.635" y2="2.54" width="0.254" layer="94" curve="-90" cap="flat"/>
<wire x1="0.635" y1="2.54" x2="0" y2="1.905" width="0.254" layer="94" curve="-90" cap="flat"/>
<wire x1="0" y1="-1.905" x2="0.635" y2="-2.54" width="0.254" layer="94" curve="-90" cap="flat"/>
<wire x1="0.635" y1="-2.54" x2="0" y2="-3.175" width="0.254" layer="94" curve="-90" cap="flat"/>
<wire x1="-2.54" y1="-7.62" x2="2.54" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="-2.54" y1="-7.62" x2="-2.54" y2="7.62" width="0.4064" layer="94"/>
<wire x1="-2.54" y1="7.62" x2="2.54" y2="7.62" width="0.4064" layer="94"/>
<wire x1="2.54" y1="-7.62" x2="2.54" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="2.54" y1="-5.08" x2="2.54" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="2.54" y2="0" width="0.4064" layer="94"/>
<wire x1="2.54" y1="0" x2="2.54" y2="2.54" width="0.4064" layer="94"/>
<wire x1="2.54" y1="2.54" x2="2.54" y2="5.08" width="0.4064" layer="94"/>
<wire x1="2.54" y1="5.08" x2="2.54" y2="7.62" width="0.4064" layer="94"/>
<wire x1="0" y1="-4.445" x2="0.635" y2="-5.08" width="0.254" layer="94" curve="-90" cap="flat"/>
<wire x1="0.635" y1="-5.08" x2="0" y2="-5.715" width="0.254" layer="94" curve="-90" cap="flat"/>
<wire x1="0.635" y1="5.08" x2="2.54" y2="5.08" width="0.1524" layer="94"/>
<wire x1="0.635" y1="2.54" x2="2.54" y2="2.54" width="0.1524" layer="94"/>
<wire x1="0.635" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="0.635" y1="-2.54" x2="2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0.635" y1="-5.08" x2="2.54" y2="-5.08" width="0.1524" layer="94"/>
<text x="-2.54" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.54" y="8.255" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="5.08" y="5.08" visible="pad" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="5.08" y="2.54" visible="pad" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="5.08" y="0" visible="pad" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="4" x="5.08" y="-2.54" visible="pad" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="5" x="5.08" y="-5.08" visible="pad" length="short" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="SPB5" urn="urn:adsk.eagle:component:7483/2" prefix="X" library_version="2">
<description>&lt;B&gt;CONNECTOR&lt;/B&gt;&lt;p&gt;
5 pins</description>
<gates>
<gate name="1" symbol="B5P" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SPB5">
<connects>
<connect gate="1" pin="1" pad="1"/>
<connect gate="1" pin="2" pad="2"/>
<connect gate="1" pin="3" pad="3"/>
<connect gate="1" pin="4" pad="4"/>
<connect gate="1" pin="5" pad="5"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:7457/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
<attribute name="POPULARITY" value="0" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="SUPPLY1" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+5V" device=""/>
<part name="U$1" library="ArduinoMegaOutline" deviceset="MEGA_DEVICE" device=""/>
<part name="X1" library="con-panduit" library_urn="urn:adsk.eagle:library:169" deviceset="057-010-" device="1" package3d_urn="urn:adsk.eagle:package:9203/1"/>
<part name="S1" library="switch-misc" library_urn="urn:adsk.eagle:library:376" deviceset="DT" device="E6" package3d_urn="urn:adsk.eagle:package:27432/1"/>
<part name="R1" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="R" device="" value="320"/>
<part name="R2" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="R" device="" value="320"/>
<part name="R3" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="R" device="" value="330"/>
<part name="R4" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="R" device="" value="330"/>
<part name="S2" library="switch-misc" library_urn="urn:adsk.eagle:library:376" deviceset="DT" device="E6" package3d_urn="urn:adsk.eagle:package:27432/1"/>
<part name="SUPPLY2" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="GND2" device=""/>
<part name="S3" library="switch-misc" library_urn="urn:adsk.eagle:library:376" deviceset="DT" device="E6" package3d_urn="urn:adsk.eagle:package:27432/1"/>
<part name="S4" library="switch-misc" library_urn="urn:adsk.eagle:library:376" deviceset="DT" device="E6" package3d_urn="urn:adsk.eagle:package:27432/1"/>
<part name="S5" library="switch-misc" library_urn="urn:adsk.eagle:library:376" deviceset="DT" device="E6" package3d_urn="urn:adsk.eagle:package:27432/1"/>
<part name="S6" library="switch-misc" library_urn="urn:adsk.eagle:library:376" deviceset="DT" device="E6" package3d_urn="urn:adsk.eagle:package:27432/1"/>
<part name="R5" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="R" device="" value="320"/>
<part name="LED1" library="led" library_urn="urn:adsk.eagle:library:259" deviceset="TLLG4400" device="" package3d_urn="urn:adsk.eagle:package:15797/1"/>
<part name="JOYSTICK" library="con-hirschmann" library_urn="urn:adsk.eagle:library:153" deviceset="SPB5" device="" package3d_urn="urn:adsk.eagle:package:7457/1"/>
<part name="SUPPLY3" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+5V" device=""/>
<part name="SUPPLY4" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="GND2" device=""/>
<part name="R6" library="ngspice-simulation" library_urn="urn:adsk.eagle:library:527439" deviceset="R" device="" value="330"/>
<part name="SUPPLY5" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="GND2" device=""/>
<part name="SUPPLY6" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="GND2" device=""/>
<part name="S7" library="switch-misc" library_urn="urn:adsk.eagle:library:376" deviceset="DT" device="E6" package3d_urn="urn:adsk.eagle:package:27432/1"/>
</parts>
<sheets>
<sheet>
<plain>
<wire x1="30.48" y1="-27.94" x2="30.48" y2="17.78" width="0.1524" layer="97"/>
<wire x1="30.48" y1="17.78" x2="43.18" y2="17.78" width="0.1524" layer="97"/>
<wire x1="43.18" y1="17.78" x2="58.42" y2="17.78" width="0.1524" layer="97"/>
<wire x1="58.42" y1="17.78" x2="71.12" y2="17.78" width="0.1524" layer="97"/>
<wire x1="71.12" y1="17.78" x2="71.12" y2="-27.94" width="0.1524" layer="97"/>
<wire x1="71.12" y1="-27.94" x2="30.48" y2="-27.94" width="0.1524" layer="97"/>
<wire x1="43.18" y1="17.78" x2="43.18" y2="12.7" width="0.1524" layer="97"/>
<wire x1="43.18" y1="12.7" x2="58.42" y2="12.7" width="0.1524" layer="97"/>
<wire x1="58.42" y1="12.7" x2="58.42" y2="17.78" width="0.1524" layer="97"/>
<text x="48.26" y="15.24" size="1.778" layer="97">DOBOT</text>
</plain>
<instances>
<instance part="SUPPLY1" gate="+5V" x="25.4" y="101.6" smashed="yes">
<attribute name="VALUE" x="23.495" y="104.775" size="1.778" layer="96"/>
</instance>
<instance part="U$1" gate="G$1" x="-40.64" y="0" smashed="yes" rot="R270"/>
<instance part="X1" gate="-1" x="40.64" y="-17.78" smashed="yes" rot="R90">
<attribute name="NAME" x="41.402" y="-16.764" size="1.524" layer="95" rot="R90"/>
<attribute name="VALUE" x="38.735" y="-20.32" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="X1" gate="-2" x="40.64" y="5.08" smashed="yes" rot="R90">
<attribute name="NAME" x="41.402" y="6.096" size="1.524" layer="95" rot="R90"/>
</instance>
<instance part="X1" gate="-3" x="45.72" y="-17.78" smashed="yes" rot="R90">
<attribute name="NAME" x="46.482" y="-16.764" size="1.524" layer="95" rot="R90"/>
</instance>
<instance part="X1" gate="-4" x="45.72" y="5.08" smashed="yes" rot="R90">
<attribute name="NAME" x="46.482" y="6.096" size="1.524" layer="95" rot="R90"/>
</instance>
<instance part="X1" gate="-5" x="50.8" y="-17.78" smashed="yes" rot="R90">
<attribute name="NAME" x="51.562" y="-16.764" size="1.524" layer="95" rot="R90"/>
</instance>
<instance part="X1" gate="-6" x="50.8" y="5.08" smashed="yes" rot="R90">
<attribute name="NAME" x="51.562" y="6.096" size="1.524" layer="95" rot="R90"/>
</instance>
<instance part="X1" gate="-7" x="55.88" y="-17.78" smashed="yes" rot="R90">
<attribute name="NAME" x="56.642" y="-16.764" size="1.524" layer="95" rot="R90"/>
</instance>
<instance part="X1" gate="-8" x="55.88" y="5.08" smashed="yes" rot="R90">
<attribute name="NAME" x="56.642" y="6.096" size="1.524" layer="95" rot="R90"/>
</instance>
<instance part="X1" gate="-9" x="60.96" y="-17.78" smashed="yes" rot="R90">
<attribute name="NAME" x="61.722" y="-16.764" size="1.524" layer="95" rot="R90"/>
</instance>
<instance part="X1" gate="-10" x="60.96" y="5.08" smashed="yes" rot="R90">
<attribute name="NAME" x="61.722" y="6.096" size="1.524" layer="95" rot="R90"/>
</instance>
<instance part="S1" gate="1" x="71.12" y="119.38" smashed="yes">
<attribute name="NAME" x="64.135" y="117.475" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="66.675" y="121.92" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="R1" gate="G$1" x="12.7" y="78.74" smashed="yes" rot="R90">
<attribute name="NAME" x="10.16" y="76.2" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="16.51" y="76.2" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="R2" gate="G$1" x="25.4" y="78.74" smashed="yes" rot="R90">
<attribute name="NAME" x="22.86" y="76.2" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="29.21" y="76.2" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="R3" gate="G$1" x="50.8" y="78.74" smashed="yes" rot="R90">
<attribute name="NAME" x="48.26" y="76.2" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="54.61" y="76.2" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="R4" gate="G$1" x="38.1" y="78.74" smashed="yes" rot="R90">
<attribute name="NAME" x="35.56" y="76.2" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="41.91" y="76.2" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="S2" gate="1" x="83.82" y="111.76" smashed="yes">
<attribute name="NAME" x="76.835" y="109.855" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="79.375" y="114.3" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="SUPPLY2" gate="G$1" x="149.86" y="116.84" smashed="yes">
<attribute name="VALUE" x="147.447" y="113.665" size="1.778" layer="96"/>
</instance>
<instance part="S3" gate="1" x="96.52" y="104.14" smashed="yes">
<attribute name="NAME" x="89.535" y="102.235" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="92.075" y="106.68" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="S4" gate="1" x="109.22" y="96.52" smashed="yes">
<attribute name="NAME" x="102.235" y="94.615" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="104.775" y="99.06" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="S5" gate="1" x="121.92" y="88.9" smashed="yes">
<attribute name="NAME" x="114.935" y="86.995" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="117.475" y="91.44" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="S6" gate="1" x="0" y="81.28" smashed="yes">
<attribute name="NAME" x="-6.985" y="79.375" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="-4.445" y="83.82" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="R5" gate="G$1" x="132.08" y="116.84" smashed="yes" rot="R90">
<attribute name="NAME" x="129.54" y="114.3" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="135.89" y="114.3" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="LED1" gate="G$1" x="109.22" y="68.58" smashed="yes" rot="R180">
<attribute name="NAME" x="105.664" y="73.152" size="1.778" layer="95" rot="R270"/>
<attribute name="VALUE" x="103.505" y="73.152" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="JOYSTICK" gate="1" x="-111.76" y="-30.48" smashed="yes">
<attribute name="VALUE" x="-114.3" y="-40.64" size="1.778" layer="96"/>
<attribute name="NAME" x="-114.3" y="-22.225" size="1.778" layer="95"/>
</instance>
<instance part="SUPPLY3" gate="+5V" x="-83.82" y="17.78" smashed="yes">
<attribute name="VALUE" x="-85.725" y="20.955" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY4" gate="G$1" x="-91.44" y="5.08" smashed="yes">
<attribute name="VALUE" x="-93.853" y="1.905" size="1.778" layer="96"/>
</instance>
<instance part="R6" gate="G$1" x="76.2" y="38.1" smashed="yes" rot="R180">
<attribute name="NAME" x="78.74" y="35.56" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="78.74" y="41.91" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="SUPPLY5" gate="G$1" x="76.2" y="-50.8" smashed="yes">
<attribute name="VALUE" x="73.787" y="-53.975" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY6" gate="G$1" x="-48.26" y="104.14" smashed="yes">
<attribute name="VALUE" x="-50.673" y="100.965" size="1.778" layer="96"/>
</instance>
<instance part="S7" gate="1" x="-33.02" y="101.6" smashed="yes">
<attribute name="NAME" x="-40.005" y="99.695" size="1.778" layer="95" rot="R90"/>
<attribute name="VALUE" x="-37.465" y="104.14" size="1.778" layer="96" rot="R90"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="N$3" class="0">
<segment>
<pinref part="X1" gate="-3" pin="S"/>
<pinref part="U$1" gate="G$1" pin="19"/>
<wire x1="45.72" y1="-30.48" x2="45.72" y2="-22.86" width="0.1524" layer="91"/>
<wire x1="-16.51" y1="-30.48" x2="45.72" y2="-30.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<wire x1="25.4" y1="-5.08" x2="45.72" y2="-5.08" width="0.1524" layer="91"/>
<pinref part="X1" gate="-4" pin="S"/>
<wire x1="45.72" y1="-5.08" x2="45.72" y2="0" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="18"/>
<wire x1="-16.51" y1="-27.94" x2="25.4" y2="-27.94" width="0.1524" layer="91"/>
<wire x1="25.4" y1="-27.94" x2="25.4" y2="-5.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<wire x1="0" y1="93.98" x2="12.7" y2="93.98" width="0.1524" layer="91"/>
<wire x1="12.7" y1="93.98" x2="25.4" y2="93.98" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="2"/>
<wire x1="12.7" y1="83.82" x2="12.7" y2="93.98" width="0.1524" layer="91"/>
<junction x="12.7" y="93.98"/>
<pinref part="R2" gate="G$1" pin="2"/>
<wire x1="25.4" y1="83.82" x2="25.4" y2="93.98" width="0.1524" layer="91"/>
<junction x="25.4" y="93.98"/>
<wire x1="25.4" y1="93.98" x2="38.1" y2="93.98" width="0.1524" layer="91"/>
<pinref part="R3" gate="G$1" pin="2"/>
<wire x1="38.1" y1="93.98" x2="50.8" y2="93.98" width="0.1524" layer="91"/>
<wire x1="50.8" y1="93.98" x2="50.8" y2="83.82" width="0.1524" layer="91"/>
<pinref part="R4" gate="G$1" pin="2"/>
<wire x1="38.1" y1="83.82" x2="38.1" y2="93.98" width="0.1524" layer="91"/>
<junction x="38.1" y="93.98"/>
<pinref part="SUPPLY1" gate="+5V" pin="+5V"/>
<wire x1="25.4" y1="99.06" x2="25.4" y2="93.98" width="0.1524" layer="91"/>
<pinref part="S6" gate="1" pin="S"/>
<wire x1="0" y1="86.36" x2="0" y2="93.98" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="5V"/>
<wire x1="-64.77" y1="12.7" x2="-83.82" y2="12.7" width="0.1524" layer="91"/>
<wire x1="-83.82" y1="12.7" x2="-83.82" y2="-27.94" width="0.1524" layer="91"/>
<pinref part="JOYSTICK" gate="1" pin="2"/>
<wire x1="-83.82" y1="-27.94" x2="-106.68" y2="-27.94" width="0.1524" layer="91"/>
<label x="-101.6" y="-27.94" size="1.778" layer="95"/>
<pinref part="SUPPLY3" gate="+5V" pin="+5V"/>
<wire x1="-83.82" y1="12.7" x2="-83.82" y2="15.24" width="0.1524" layer="91"/>
<junction x="-83.82" y="12.7"/>
</segment>
</net>
<net name="GND2" class="0">
<segment>
<pinref part="S2" gate="1" pin="S"/>
<wire x1="83.82" y1="116.84" x2="83.82" y2="127" width="0.1524" layer="91"/>
<wire x1="83.82" y1="127" x2="96.52" y2="127" width="0.1524" layer="91"/>
<pinref part="S3" gate="1" pin="S"/>
<wire x1="96.52" y1="109.22" x2="96.52" y2="127" width="0.1524" layer="91"/>
<pinref part="S4" gate="1" pin="S"/>
<wire x1="109.22" y1="101.6" x2="109.22" y2="127" width="0.1524" layer="91"/>
<wire x1="109.22" y1="127" x2="96.52" y2="127" width="0.1524" layer="91"/>
<junction x="96.52" y="127"/>
<pinref part="S5" gate="1" pin="S"/>
<wire x1="121.92" y1="93.98" x2="121.92" y2="127" width="0.1524" layer="91"/>
<wire x1="121.92" y1="127" x2="109.22" y2="127" width="0.1524" layer="91"/>
<junction x="109.22" y="127"/>
<wire x1="132.08" y1="127" x2="121.92" y2="127" width="0.1524" layer="91"/>
<junction x="121.92" y="127"/>
<pinref part="R5" gate="G$1" pin="2"/>
<wire x1="132.08" y1="121.92" x2="132.08" y2="127" width="0.1524" layer="91"/>
<wire x1="132.08" y1="127" x2="149.86" y2="127" width="0.1524" layer="91"/>
<junction x="132.08" y="127"/>
<pinref part="SUPPLY2" gate="G$1" pin="GND2"/>
<wire x1="149.86" y1="127" x2="149.86" y2="119.38" width="0.1524" layer="91"/>
<pinref part="S1" gate="1" pin="S"/>
<wire x1="71.12" y1="124.46" x2="71.12" y2="127" width="0.1524" layer="91"/>
<wire x1="83.82" y1="127" x2="71.12" y2="127" width="0.1524" layer="91"/>
<junction x="83.82" y="127"/>
</segment>
<segment>
<pinref part="SUPPLY4" gate="G$1" pin="GND2"/>
<wire x1="-91.44" y1="7.62" x2="-91.44" y2="10.16" width="0.1524" layer="91"/>
<pinref part="JOYSTICK" gate="1" pin="1"/>
<wire x1="-106.68" y1="-25.4" x2="-86.36" y2="-25.4" width="0.1524" layer="91"/>
<wire x1="-86.36" y1="-25.4" x2="-86.36" y2="10.16" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="GND@2"/>
<wire x1="-86.36" y1="10.16" x2="-64.77" y2="10.16" width="0.1524" layer="91"/>
<label x="-101.6" y="-25.4" size="1.778" layer="95"/>
<wire x1="-91.44" y1="10.16" x2="-86.36" y2="10.16" width="0.1524" layer="91"/>
<junction x="-86.36" y="10.16"/>
</segment>
<segment>
<pinref part="X1" gate="-10" pin="S"/>
<wire x1="60.96" y1="0" x2="76.2" y2="0" width="0.1524" layer="91"/>
<wire x1="76.2" y1="0" x2="76.2" y2="-45.72" width="0.1524" layer="91"/>
<pinref part="SUPPLY5" gate="G$1" pin="GND2"/>
<wire x1="76.2" y1="-45.72" x2="76.2" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="76.2" y1="-45.72" x2="40.64" y2="-45.72" width="0.1524" layer="91"/>
<wire x1="40.64" y1="-45.72" x2="40.64" y2="-55.88" width="0.1524" layer="91"/>
<junction x="76.2" y="-45.72"/>
<pinref part="U$1" gate="G$1" pin="GND@7"/>
<wire x1="-59.69" y1="-45.72" x2="-73.66" y2="-45.72" width="0.1524" layer="91"/>
<pinref part="JOYSTICK" gate="1" pin="5"/>
<wire x1="-73.66" y1="-45.72" x2="-96.52" y2="-45.72" width="0.1524" layer="91"/>
<wire x1="-96.52" y1="-45.72" x2="-96.52" y2="-35.56" width="0.1524" layer="91"/>
<wire x1="-96.52" y1="-35.56" x2="-106.68" y2="-35.56" width="0.1524" layer="91"/>
<label x="-101.6" y="-35.56" size="1.778" layer="95"/>
<wire x1="40.64" y1="-55.88" x2="-73.66" y2="-55.88" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="-55.88" x2="-73.66" y2="-45.72" width="0.1524" layer="91"/>
<junction x="-73.66" y="-45.72"/>
</segment>
<segment>
<pinref part="SUPPLY6" gate="G$1" pin="GND2"/>
<pinref part="S7" gate="1" pin="S"/>
<wire x1="-48.26" y1="106.68" x2="-33.02" y2="106.68" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="S1" gate="1" pin="P"/>
<wire x1="-52.07" y1="60.96" x2="12.7" y2="60.96" width="0.1524" layer="91"/>
<wire x1="12.7" y1="60.96" x2="71.12" y2="60.96" width="0.1524" layer="91"/>
<wire x1="71.12" y1="114.3" x2="71.12" y2="60.96" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="1"/>
<wire x1="12.7" y1="73.66" x2="12.7" y2="60.96" width="0.1524" layer="91"/>
<junction x="12.7" y="60.96"/>
<pinref part="U$1" gate="G$1" pin="48"/>
<wire x1="-52.07" y1="-43.18" x2="-52.07" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="44"/>
<wire x1="83.82" y1="53.34" x2="25.4" y2="53.34" width="0.1524" layer="91"/>
<wire x1="25.4" y1="53.34" x2="-48.26" y2="53.34" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="53.34" x2="-48.26" y2="-43.18" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="-43.18" x2="-46.99" y2="-43.18" width="0.1524" layer="91"/>
<pinref part="S2" gate="1" pin="P"/>
<wire x1="83.82" y1="106.68" x2="83.82" y2="53.34" width="0.1524" layer="91"/>
<pinref part="R2" gate="G$1" pin="1"/>
<wire x1="25.4" y1="73.66" x2="25.4" y2="53.34" width="0.1524" layer="91"/>
<junction x="25.4" y="53.34"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="40"/>
<wire x1="-41.91" y1="-43.18" x2="-43.18" y2="-43.18" width="0.1524" layer="91"/>
<wire x1="-43.18" y1="-43.18" x2="-43.18" y2="45.72" width="0.1524" layer="91"/>
<wire x1="-43.18" y1="45.72" x2="38.1" y2="45.72" width="0.1524" layer="91"/>
<pinref part="S3" gate="1" pin="P"/>
<wire x1="38.1" y1="45.72" x2="96.52" y2="45.72" width="0.1524" layer="91"/>
<wire x1="96.52" y1="99.06" x2="96.52" y2="45.72" width="0.1524" layer="91"/>
<pinref part="R4" gate="G$1" pin="1"/>
<wire x1="38.1" y1="73.66" x2="38.1" y2="45.72" width="0.1524" layer="91"/>
<junction x="38.1" y="45.72"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="S6" gate="1" pin="P"/>
<wire x1="0" y1="76.2" x2="0" y2="25.4" width="0.1524" layer="91"/>
<wire x1="0" y1="25.4" x2="0" y2="-7.62" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="2"/>
<wire x1="0" y1="-7.62" x2="-16.51" y2="-7.62" width="0.1524" layer="91"/>
<pinref part="R5" gate="G$1" pin="1"/>
<wire x1="132.08" y1="111.76" x2="132.08" y2="25.4" width="0.1524" layer="91"/>
<wire x1="132.08" y1="25.4" x2="0" y2="25.4" width="0.1524" layer="91"/>
<junction x="0" y="25.4"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="S5" gate="1" pin="P"/>
<wire x1="121.92" y1="83.82" x2="121.92" y2="33.02" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="GND@6"/>
<wire x1="121.92" y1="33.02" x2="50.8" y2="33.02" width="0.1524" layer="91"/>
<wire x1="50.8" y1="33.02" x2="-59.69" y2="33.02" width="0.1524" layer="91"/>
<wire x1="-59.69" y1="33.02" x2="-59.69" y2="-43.18" width="0.1524" layer="91"/>
<pinref part="R3" gate="G$1" pin="1"/>
<wire x1="50.8" y1="73.66" x2="50.8" y2="33.02" width="0.1524" layer="91"/>
<junction x="50.8" y="33.02"/>
</segment>
</net>
<net name="VRY" class="0">
<segment>
<pinref part="JOYSTICK" gate="1" pin="4"/>
<wire x1="-106.68" y1="-33.02" x2="-76.2" y2="-33.02" width="0.1524" layer="91"/>
<wire x1="-76.2" y1="-33.02" x2="-76.2" y2="-2.54" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="A1"/>
<wire x1="-76.2" y1="-2.54" x2="-64.77" y2="-2.54" width="0.1524" layer="91"/>
<label x="-101.6" y="-33.02" size="1.778" layer="95"/>
</segment>
</net>
<net name="VRX" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="A0"/>
<wire x1="-64.77" y1="0" x2="-78.74" y2="0" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="0" x2="-78.74" y2="-30.48" width="0.1524" layer="91"/>
<pinref part="JOYSTICK" gate="1" pin="3"/>
<wire x1="-78.74" y1="-30.48" x2="-106.68" y2="-30.48" width="0.1524" layer="91"/>
<label x="-101.6" y="-30.48" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="13"/>
<wire x1="-16.51" y1="21.59" x2="-16.51" y2="20.32" width="0.1524" layer="91"/>
<wire x1="-16.51" y1="20.32" x2="-30.48" y2="20.32" width="0.1524" layer="91"/>
<wire x1="-30.48" y1="20.32" x2="-30.48" y2="38.1" width="0.1524" layer="91"/>
<pinref part="R6" gate="G$1" pin="2"/>
<wire x1="-30.48" y1="38.1" x2="71.12" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="R6" gate="G$1" pin="1"/>
<wire x1="81.28" y1="38.1" x2="109.22" y2="38.1" width="0.1524" layer="91"/>
<pinref part="LED1" gate="G$1" pin="A"/>
<wire x1="109.22" y1="38.1" x2="109.22" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="LED1" gate="G$1" pin="C"/>
<pinref part="S4" gate="1" pin="P"/>
<wire x1="109.22" y1="73.66" x2="109.22" y2="78.74" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="36"/>
<wire x1="109.22" y1="78.74" x2="109.22" y2="91.44" width="0.1524" layer="91"/>
<wire x1="-36.83" y1="-43.18" x2="-36.83" y2="40.64" width="0.1524" layer="91"/>
<wire x1="-36.83" y1="40.64" x2="101.6" y2="40.64" width="0.1524" layer="91"/>
<wire x1="101.6" y1="40.64" x2="101.6" y2="78.74" width="0.1524" layer="91"/>
<wire x1="101.6" y1="78.74" x2="109.22" y2="78.74" width="0.1524" layer="91"/>
<junction x="109.22" y="78.74"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="S7" gate="1" pin="P"/>
<pinref part="U$1" gate="G$1" pin="32"/>
<wire x1="-33.02" y1="96.52" x2="-31.75" y2="96.52" width="0.1524" layer="91"/>
<wire x1="-31.75" y1="96.52" x2="-31.75" y2="-43.18" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
<note version="8.4" severity="warning">
Since Version 8.4, EAGLE supports properties for SPICE simulation. 
Probes in schematics and SPICE mapping objects found in parts and library devices
will not be understood with this version. Update EAGLE to the latest version
for full support of SPICE simulation. 
</note>
</compatibility>
</eagle>
