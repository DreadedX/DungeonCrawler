// Run this with nodejs to generate a json file which contains all files needed in the l
fs = require('fs');

// Types
var TYPE_RANGED = 0;
var TYPE_MELEE = 1;
var TYPE_PASSIVE = 2;

var TYPE_ARROW = 0;
var TYPE_FIRE = 1;
var TYPE_HEALING = 2;

var data = { "items": [

    ["Sword", 100.0, 10.0, TYPE_MELEE],
    ["Bow", 140.0, 5.0, TYPE_RANGED, TYPE_ARROW],
    ["Staff of Fire", 120.0, 7.5, TYPE_RANGED, TYPE_FIRE],
    ["Ring", 50.0, 0.2, TYPE_PASSIVE, TYPE_HEALING],
    ["Crossbow", 160.0, 6.5, TYPE_ARROW]
], "modifiers": [

    ["Keen", 1.12, 1.0],
    ["Superior", 1.64, 1.0],
    ["Forceful", 1.32, 1.0],
    ["Broken", 0.32, 1.0],
    ["Damaged", 0.73, 1.0],
    ["Shoddy", 0.59, 1.0],
    ["Hurtful", 1.21, 1.0],
    ["Strong", 1.32, 1.0],
    ["Unpleasant", 1.45, 1.0],
    ["Weak", 0.64, 1.0],
    ["Ruthless", 1.12, 1.0],
    ["Godly", 1.60, 1.0],
    ["Demonic", 1.21, 1.0]
]};

fs.writeFile('items.json', JSON.stringify(data), function (err) {
    if (err) return console.log(err);
});
