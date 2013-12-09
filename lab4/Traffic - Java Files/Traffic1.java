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
		System.out.println("Please select the number of cars per clock tick:");
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
		
		//Create new cars, add cars to queue;
		generateCars();
		
		//Loops through till all of the lists are empty
		while (!queueList.get(0).isEmpty() || !queueList.get(1).isEmpty() || !queueList.get(2).isEmpty() || !queueList.get(3).isEmpty()) {        	
			CarThread[] threads = new CarThread[4];

			Vector<CarThread> n = queueList.get(0);
			Vector<CarThread> s = queueList.get(1);
			Vector<CarThread> e = queueList.get(2);
			Vector<CarThread> w = queueList.get(3);
	        
			boolean mod = true;

	        /* If it is not empty, the thread is removed and is allowed to access the semaphore */
	        if(!n.isEmpty()){
	            threads[0] = n.remove(0);
	            threads[0].drive();
	            mod = false;
	        }
	        if(!s.isEmpty()){
	            threads[1] = s.remove(0);
	            threads[1].drive();
	            mod = false;
	        }
	        if(!e.isEmpty()){
	            threads[2] = e.remove(0);
	            threads[2].drive();
	            mod = false;
	        }
	        if(!w.isEmpty()){
	            threads[3] = w.remove(0);
	            threads[3].drive();
	            mod = false;
	        }
	        if(mod){
	        	incrementClock();
	        }
		}
		System.exit(1);
	}
	
	/*
	 * Generates Cars and places them in their respective streets.
	 * Cars are generated up to a certain, max number of clock ticks.
	 */
	private static void generateCars() {
		System.out.println("\nClock " + clock);
    	
		// Every time cars are generated, a random number of cars (to a point) are created and added to a random street

		if (clock < maxNumClockTicks) {
			int carsPerClockTick = (int) (Math.random()*numCarsPerTick);
			while(clock == 0 && carsPerClockTick == 0) {
				carsPerClockTick = (int) (Math.random()*numCarsPerTick);
			}
			System.out.println(carsPerClockTick);
    		for (int i = 0; i < carsPerClockTick; i++) {
    			int direction = (int) (Math.random() * 4);
    			
    			CarThread ct = new CarThread(currCarId++, direction);			
        		queueList.get(direction).add(ct);
        		ct.start();
    		}
    	}
		
		for (int i = 0; i < 4; i++) {
			System.out.println(queueList.get(i).toString());
		}
	}
	
	private static void incrementClock() {
		clock++;
		generateCars();
	}
	
	/*
	 * Private inner class CarThread
	 * Combines both threads and cars, and provides a custom run implementation.
	 */
	private static class CarThread extends Thread {
		private int id;
		private boolean running;
		
		CarThread(int id, int direction) {
			this.id = id;
			this.running = true;
		}

		public void run() {
			while(running) {}
		}
		
		private void drive(){
			try {
				intersection_semaphore.acquire();
				incrementClock();
				intersection_semaphore.release();
				running = false;
			} catch (InterruptedException e) {
				e.printStackTrace();
			} 
		}

		public String toString() {
			return "Car " + id;
		}
	}
}
