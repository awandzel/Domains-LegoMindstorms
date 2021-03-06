package edu.umich.eecs.soar.lego;

import java.io.IOException;

import edu.umich.eecs.soar.lego.core.LegoCore;

public class LegoWorld
{
	private static final String AgentsFolder = "./TutorialAgents/";
	private static final String MapsFolder = "./maps/";
	private static final String SoarDebuggerJarPath = System.getenv("SOAR_HOME") + "/SoarJavaDebugger.jar";
	private static final String AgentFile = "Advanced-Stage4-completed";
	private static final String Map = "AdvancedTutorialTestMap";
	private static final Integer seed = new Integer((int)(Math.random() * 10000.0));
	private static final int TimeDelayMiliseconds = 0;
	
	public static void main(String[] args) throws IOException
	{		
		LegoCore lego = new LegoCore();
		lego.run(TimeDelayMiliseconds, SoarDebuggerJarPath, AgentFile, Map, seed, AgentsFolder, MapsFolder);
	}
}
