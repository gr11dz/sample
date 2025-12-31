create trigger t_Checklist_FlightReady on CheckList
after INSERT
as
	declare @ID int , @air_ID int, @storage bit , @fuel bit , @clearance bit
	select @ID = cl_ID , @air_ID = cl_AircraftID, @storage = cl_storage , @fuel = cl_fuel , @clearance = cl_clearance from INSERTED
	
	IF @fuel = 1 and @storage = 1 and @clearance = 1 
		UPDATE CheckList
		set cl_Ready = 1
		where cl_ID = @ID

create or alter function PilotDetails(@ID int) returns table
as return
(
	with findAircraft (AircraftCall , pilotID) as
	(
		select air.air_callsign , crew.cr_firstPilotID
		from Aircraft air inner join Crew crew on crew.cr_ID = air.air_crewID
		group by air.air_callsign , crew.cr_firstPilotID
	)
	select  p.pil_name as 'First Name' , p.pil_lname as 'Last Name' , p.pil_age as 'Age' , p.pil_flightHours as 'Flight Hours' , p.pil_nationality as 'Nationality' , fa.AircraftCall as 'Aircraft Callsign'
	from findAircraft fa inner join Pilots p on p.pil_ID = fa.pilotID
	where fa.pilotID = @ID
);
select * from PilotDetails(3)


create or alter function f__Ticket__Terminal_find(@ticket_ID int) returns table 
as return
(
	with findAirline(terminalID , airlineName , firstName , lastName , tiFrom , destination , departure , arrival) as
	(
		select ti.ti_terminalID, ai.al_name , ti.ti_passengerName , ti.ti_passengerLname , ti.ti_from , ti.ti_destination , ti.ti_departure , ti.ti_arrival
		from Airline ai inner join Ticket ti on ti.ti_airlineID = ai.al_ID
	)
	select fa.firstName as 'First Name' , fa.lastName as 'Last Name' , fa.departure as 'Departure' , fa.tiFrom as 'From' , fa.destination as 'Destination' , fa.arrival as 'Arrival' , fa.airlineName as 'Airline' , te.ter_name 'Terminal Name'
	from findAirline fa inner join Terminal te on fa.terminalID = te.ter_ID

)
select * from f__Ticket__Terminal_find(1)

create or alter procedure SP__AircraftModel_findValue @amID int , @value int output
as
begin
	select @value = am.am_value
	from AircraftModel am inner join Manufacturer m on am.am_manID = m.man_ID
	where am.am_ID = @amID
	return
end

create or alter trigger t_TransactionsDetails on TransactionsDetails
after insert
as
	declare @ID int , @terminalID int , @amID int, @amount int , @value bigint
	select @ID = td_ID , @terminalID = td_trnID , @amount = td_amount from INSERTED

	select @amID = t.trn_amID
	from TransactionsDetails td inner join Transactions t on t.trn_ID = td.td_trnID
	where td_ID = @ID

	execute SP__AircraftModel_findValue @amID , @value output

	print @value
	Update TransactionsDetails
	set td_total = @value * @amount
	where td_ID = @ID

