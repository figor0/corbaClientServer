import QtQuick 2.0
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

Item {
    id: root
    property int action_type: 0
    function refresh(){
        menu.title = "Ничего не делать";
        action_type = 0;
    }
    MenuBar{
        id: players
        anchors.fill: parent
        Menu{
            id: menu
            title: qsTr("Ничего не делать")
            Action {
                text: qsTr("Инвертировать записи")
                onTriggered: {
                    action_type = 1;
                    menu.title = text;
                }
            }
            Action {
                text: qsTr("К маленькой букве")
                onTriggered: {
                   menu.title = text;
                   action_type = 2;
                }
            }
            Action {
                text: qsTr("К большой букве")
                onTriggered: {
                   menu.title = text;
                   action_type = 3;
                }
            }
        }
    }
}
