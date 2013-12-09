package edu.uwec.cs.sheaffmc.lab4;

import java.util.Scanner;
import java.util.Vector;
import java.util.concurrent.*;

public class Traffic {
	
	private static Semaphore intersection_semaphore;

	private static Integer clock;
	private static int currCarId;
	private static int numCarsPerTick;
	private static int maxNumClockTicks;
	private static Vector<Vector<CarThread>> queueList;
	
	public static void main(String[] args) {
		
		//Initializing variables
		intersection_semaphore = new Semaphore(1);
		clock = new Integer(0);
		currCarId = 0;
		
		//Input for number of cars per clock tick
		System.out.println("Please select the max number of cars per clock tick:");
		Scanner in = new Scanner(System.in);
		numCarsPerTick = in.nextInt();
		
		//Input for max number of clock ticks
		System.out.println("Please select max number of clock ticks to which you can make cars:");
		maxNumClockTicks = in.nextInt();
		in.close();
		
		//Creates a new ArrayList, fills it with 4 linked lists, trims it to the appropriate size
		queueList = new Vector<Vector<CarThread>>();
		for (int i = 0; i < 4; i++) {
			queueList.add(new Vector<CarThread>());
		}	
		queueList.trimToSize();
		
		// Create new cars, add cars to queue; This starts the entire process. 
		// In order to see the program run, there must be cars generated.
		generateCars();
		
	}
	
	/*
	 * Generates Cars and places them in their respective streets.
	 * Cars are generated up to a certain, max number of clock ticks.
	 */
	private static void generateCars() {
		
		// Printout showing the current car allocation
		System.out.println("\nClock: " + clock);
		
		// Every time cars are generated, a random number of cars (to a point) are created and added to a random street
		if (clock < maxNumClockTicks) {
			int carsPerClockTick = (int) (Math.random()*numCarsPerTick);
			//Ensures you start off with at least one car.
			while(clock == 0 && carsPerClockTick == 0) {
				carsPerClockTick = (int) (Math.random()*numCarsPerTick);
			}
			System.out.println(carsPerClockTick);
			for (int i = 0; i < carsPerClockTick; i++) {
    			int direction = (int) (Math.random() * 4);
    			
    			//Cars are created, added, and then the thread starts.
    			CarThread ct = new CarThread(currCarId++, direction);			
        		queueList.get(direction).add(ct);
        		ct.start();
    		}
    	}
		
		for (int i = 0; i < 4; i++) {
			System.out.println(queueList.get(i).toString());
		}
	}
	
	/*
	 * Whenever the clock is incremented, more cars are generated.
	 */
	private static void drive() {
		clock++;
		generateCars();
	}
	
	
	/*
	 * Private inner class CarThread
	 * Combines both threads and cars, and provides a custom run implementation.
	 */
	private static class CarThread extends Thread {
		
		private int id;
		private int dir;
		
		CarThread(int id, int direction) {
			this.id = id;
			this.dir = direction;
		}

		public void run() {
			try {
				intersection_semaphore.acquire();
				drive();
				intersection_semaphore.release();
				queueList.get(dir).remove(queueList.get(dir).indexOf(this));
			} catch (InterruptedException e) {
				e.printStackTrace();
			}	
		}
		
		public String toString() {
			return "Car " + id;
		}
	}
	
}
