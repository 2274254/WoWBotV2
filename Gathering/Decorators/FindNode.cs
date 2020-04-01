using Agony;
using Agony.SDK.Enumerations;
using Agony.SDK.Pathing;
using Agony.SDK.TreeSharp;
using Agony.SDK.Utils;
using SharpDX;
using System;
using System.Xml;
using Action = Agony.SDK.TreeSharp.Action;

namespace Gathering.Decorators
{
    public static class FindNode
    {
        static bool ShouldTakeAction()
        {
            if
            (
                Gathering.NodeObject == null ||
                Gathering.NodeObject.Type == Agony.WoWObjectType.Invalid
            )
            {
                Gathering.NodeObject = null;
                return true;
            }
            return false;
        }

        static Action TakeAction()
        {
            return new Action(a =>
            {
                try
                {
                    Logger.Log(LogLevel.Info, "[Gathering] Searching node.");
                    Gathering.NodeObject = null;
                    //Look for any NODE arround...

                    //If no nodes arround, move to a hotspot...
                    if (Gathering.NodeObject == null)
                    {
                        var playerPosition = Game.Me.Position;
                        XmlNode hotspots = Gathering.Profile["HBProfile"]["Hotspots"];
                        if (Gathering.HotspotIndex == -1)
                        {
                            Gathering.HotspotIndex = 0;
                            float currentDistance = float.MaxValue;
                            //Find closest node
                            for(var i = 0; i < hotspots.ChildNodes.Count; i++)
                            {
                                var hotspot = hotspots.ChildNodes.Item(i);
                                var hotspotDistance = Vector3.Distance(new Vector3(float.Parse(hotspot.Attributes.GetNamedItem("X").Value), float.Parse(hotspot.Attributes.GetNamedItem("Y").Value), float.Parse(hotspot.Attributes.GetNamedItem("Z").Value)), playerPosition);
                                if (hotspotDistance < currentDistance)
                                {
                                    Gathering.HotspotIndex = i;
                                    currentDistance = hotspotDistance;
                                }
                            }
                        }
                        else if(Gathering.HotspotIndex == hotspots.ChildNodes.Count)
                        {
                            Gathering.HotspotIndex = 0;
                        }
                        var currentHotspot = hotspots.ChildNodes.Item(Gathering.HotspotIndex);
                        var x = float.Parse(currentHotspot.Attributes.GetNamedItem("X").Value);
                        var y = float.Parse(currentHotspot.Attributes.GetNamedItem("Y").Value);
                        var z = float.Parse(currentHotspot.Attributes.GetNamedItem("Z").Value);
                        var hotspotPosition = new Vector3(x, y, z);
                        var distance = Vector3.Distance(hotspotPosition, playerPosition);

                        Logger.Log(LogLevel.Debug, string.Format("Distance: {0}", distance));
                        Logger.Log(LogLevel.Debug, string.Format("Pos: ({0}, {1}, {2})", playerPosition.X, playerPosition.Y, playerPosition.Z));
                        Logger.Log(LogLevel.Debug, string.Format("Target: ({0}, {1}, {2}", hotspotPosition.X, hotspotPosition.Y, hotspotPosition.Z));
                        Logger.Log(LogLevel.Debug, string.Format("CurrentSpeed: {0}", Game.Me.CurrentSpeed));

                        if (distance < 50)
                        {
                            Gathering.HotspotIndex++;
                        }
                        else
                        {
                            MoveTo.Move(hotspotPosition);
                        }
                    }
                }
                catch(Exception ex)
                {
                    Logger.Log(LogLevel.Error, ex.Message + Environment.NewLine + ex.StackTrace);
                }
            });
        }

        public static Composite BehaviorComposite => new Decorator(t => ShouldTakeAction(), TakeAction());
    }
}