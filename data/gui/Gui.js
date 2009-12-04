{
  // Each item is either a "node", containing children, or a "property",
  // containing a textual or numerical value. Inspired mostly by JSON
  // notation, although variables or a script interpreter do not exist.
  //
  // In here:
  // t means top
  // l means left
  // r means right
  // b means bottom
  // s means scale (percent values, 1 to 0)
  // p means pixel (exact values)
  // see http://www.cegui.org.uk/wiki/index.php/HOWTO:_Use_the_Unified_Positions_and_Sizes_System
  // !!everything is relitive to top-left of the parent window!!
  //
  //  {{ls, lp}, {ts, tp}, {rs, rp}, {bs, bp}}
  "Name": "Menu/Background",
  "UnifiedSize": "{{0.0,0.0},{0.0,0.0},{1.0,0},{1.0,0}}",
  "Type": "WindowsLook/StaticImage",
  "Children": [
   {
    "Name": "Menu/NewGame",
    "Type": "WindowsLook/Button",
    "UnifiedSize": "{{0.0,2.0},{0.0,2.0},{1.0,2.0},{0.4,0.0}}",
    "NormalImage": "{\"set\":\"Buttons\", \"image\": \"ButtonUp\"}"
   },
   {
    "Name": "Menu/SaveGame",
    "Type": "WindowsLook/Button",
    "UnifiedSize": "{{0.2,0.0},{0.4,0.0},{0.6,0.0},{0.6,0.0}}"
   }
  ]
}
